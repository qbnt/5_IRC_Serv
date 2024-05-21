/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:48:12 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/21 12:47:27 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_setNonBlocking(int fd){
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0){
		std::cout << "Error: Cannot set socket to non-blocking" << std::endl;
		if (fd != this->_socketFd)
			this->deleteClient(fd);
	}
}

void	Server::_createClientFds(void){
	if (this->_clientsFd)
		delete [] this->_clientsFd;
	this->_clientsFd = new struct pollfd[this->_clientsReady.size() + 1];
	this->_clientsFd[0].fd = this->_socketFd;
	this->_clientsFd[0].events = POLLIN;
	this->_clientsFd[0].revents = 0;
	for (size_t i = 0; i < this->_clientsReady.size(); i++){
		this->_clientsFd[i + 1].fd = this->_clientsReady[i]->getClientSocket();
		this->_clientsFd[i + 1].events = POLLIN;
		this->_clientsFd[i + 1].revents = 0;
	}
}

void	Server::_acceptConnection(){
	struct sockaddr_in6	address;
	socklen_t			addrlen = sizeof(address);
	int					newsockfd = accept(this->_socketFd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
	if (newsockfd < 0){
		std::cout << "Error: couldn't accept connection." << std::endl;
		return ;
	}
	//we got a connection so we add the client to the list
	char str_ipv6_addr[INET6_ADDRSTRLEN];
	this->addClient(newsockfd, inet_ntop(AF_INET6, &address, str_ipv6_addr, INET6_ADDRSTRLEN), DEFAULT_PORT);
	std::cout << "server: connection received from: " << inet_ntop(AF_INET6, &address, str_ipv6_addr, INET6_ADDRSTRLEN)
		<< " port: " << ntohs(address.sin6_port) << std::endl;
}

void	Server::_parsMessage(std::string msg, Client* client){
	if (msg.at(msg.size() - 1) == '\n'){
		std::vector<std::string> cmd = ft_split(client->getMessage() + msg, '\n');

		client->setMessage("");
		for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end(); it++) {
				this->_commands->handle(client, *it);
		}
	}
	else
		client->setMessage(client->getMessage() + msg);
}

void	Server::_clientMessage(Client*	client) {

	char buff[BUFFER_SIZE + 1];
	while (true) {
		int res = recv(client->getClientSocket(), buff, sizeof(buff), 0);
		if (res < 0) {
			break;
		} else if (!res) {
			this->deleteClient(client->getClientSocket());
			break;
		} else {
			buff[res] = '\0';
			std::string msg = buff;
			_parsMessage(msg, client);
		}
	}
}

int stop = 1;

void	Server::_waitForConnections(){

	int	socketActivity = poll(this->_clientsFd, this->_clientsReady.size() + 1, - 1);
	if (socketActivity < 0 && stop == 1){
		std::cout << "Error: No socket activity." << std::endl;
		return ;
	}

	for (unsigned int i = 0; i < _clientsReady.size() + 1; i++) {
			short revents = this->_clientsFd[i].revents;
			if (revents == 0) {
				continue;
			}
			if (this->_clientsFd[i].fd == this->_socketFd) {
				this->_acceptConnection();
			} else if (i > 0) {
				Client*	client = this->_clientsReady[i - 1];
				if ((revents & POLLIN) && client && client->getClientSocket())
					_clientMessage(client);
				else if (revents & (POLLERR | POLLHUP | POLLNVAL)) {
					std::cerr << "Erreur : Problème avec fd " << _clientsFd[i].fd << std::endl;
					deleteClient(_clientsFd[i].fd);
				}
		}
	}
}

void	signalHandler(int signal){
	if (signal == SIGINT)
		stop = 0;
}

void	Server::IRC(){
	int 					opt = 1;
	struct sockaddr_in6		adress;
	int						adresslen = sizeof(adress);

	signal(SIGINT, signalHandler);
	//creation of socket
	if (_socketFd == SOCKET_ERROR)
		throw(Socket());
	if (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
		throw(SocketOptions());

	//type of socket and bind to the port
	adress.sin6_family = AF_INET6;
	adress.sin6_addr = in6addr_any;
	adress.sin6_port = htons(this->_port);
	adress.sin6_flowinfo = 0;
	adress.sin6_scope_id = 0;
	if (bind(this->_socketFd, (struct sockaddr*)&adress, adresslen) < 0){
		std::cout << "Error: Couldn't bind socket" << std::endl;
		close(this->_socketFd);
		return ;
	}

	std::cout << "ircserv connected on port: " << this->_port << std::endl;

	//creation of clientFd vector and listen loop
	if (listen(_socketFd, 32) < 0){
		std::cout << "Error: Cannot lisent socket" << std::endl;
		return ;
	}
	std::cout << "Server waiting for connections..." << std::endl;
	this->_createClientFds();
	while (stop)
		this->_waitForConnections();
}

Client*	Server::getClient(std::string const& cl){
	std::vector<Client*>::iterator it = _clientsReady.begin();
	while (it != _clientsReady.end()){
		if ((*it)->getNickname() == cl)
			return (*it);
		it++;
	}
	return NULL;
}

int	Server::addClient(int socket, std::string ip, int port){
	std::string newip = ip;
	if (newip.find("::ffff:") != std::string::npos)
		newip = newip.substr(7);
	else if (newip.find("::") != std::string::npos)
		newip = newip.substr(2);
	if (newip.empty() || newip == "1")
		newip = "127.0.0.1";
	this->_clientsReady.push_back(new Client(this, socket, newip, port));
	std::cout << "Client add to vector: " << socket << std::endl;
	this->_setNonBlocking(socket);
	this->_createClientFds();
	return (_clientsReady.size());
}

Server::Server(int port, std::string const& password): _port(port), _password(password){
	_serverName = DEFAULT_SERVER_NAME;
	_socketFd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	_clientsFd = NULL;
	_startTime = timeString();
	_commands = new CommandsUse(this);
	this->IRC();
}

Server::~Server(){
	for (unsigned int i = 0; i < _clientsReady.size(); i++)
		deleteClient(_clientsReady[i]->getClientSocket());
	_clientsReady.clear();
	for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
		delete *it;
	_channels.clear();
	delete this->_commands;
	delete [] this->_clientsFd;
	close(_socketFd);
}

Server& Server::operator=(Server const& cp){
	if (this != &cp){
		_socketFd = cp._socketFd;
	}
	return (*this);
}

ssize_t	Server::send(std::string message, int fd) const{
	if (message[message.size() - 1] != '\n')
		message += "\n";
	ssize_t send = ::send(fd, message.c_str(), message.length(), 0);
	if (send != (ssize_t)message.length())
		std::cout << "Message sent incomplete" << std::endl;
	return (send);
}

void	Server::broadcast(std::string const& message) const{
	for (unsigned int i = 0; i < _clientsReady.size(); i++){
		this->send(message, _clientsReady[i]->getClientSocket());
	}
}

void	Server::broadcast(std::string const& message, int exclude) const{
	for (unsigned int i = 0; i < _clientsReady.size(); i++){
		if (_clientsReady[i]->getClientSocket() != exclude)
			this->send(message, _clientsReady[i]->getClientSocket());
	}
}

Client*	Server::getClientsFd(int fd){
	for (unsigned int i = 0; i < this->_clientsReady.size(); i++){
		if (this->_clientsReady[i]->getClientSocket() == fd)
			return (this->_clientsReady[i]);
	}
	return (NULL);
}

Channel*	Server::createChannel(std::string const& name, std::string const& pass, Client* client){
	Channel* channel = new Channel(name, pass, client, this);
	_channels.push_back(channel);
	return (channel);
}

void	Server::broadcastChannel(std::string const& msg, int fd_exclude, Channel const* channel) const{
	std::vector<Client*> clients = channel->getClients();

	for (unsigned int i = 0; i < clients.size(); i++){
		if (clients[i]->getClientSocket() != fd_exclude)
			this->send(msg, clients[i]->getClientSocket());
	}
}

void	Server::broadcastChannel(std::string const& msg, Channel const* channel) const{
	std::vector<Client*> clients = channel->getClients();

	for (unsigned int i = 0; i < clients.size(); i++){
			this->send(msg, clients[i]->getClientSocket());
	}
}

int	Server::deleteClient(int socket){
	std::string empty = "";

	for (std::vector<Client*>::iterator it = _clientsReady.begin(); it != _clientsReady.end(); it++){
		if ((*it)->getClientSocket() == socket){
			for (unsigned int i = 0; i < _channels.size(); i++){
				if (_channels[i]->isInChan(*it)){
					_channels[i]->removeUser(*it, empty);
				}
			}
			delete (*it);
			_clientsReady.erase(it);
			break;
		}
	}
	this->_createClientFds();
	close(socket);
	return (this->_clientsReady.size());
}

std::vector<std::string>	Server::getNicknames(){
	std::vector<std::string> nicknames;
	std::vector<Client*>::iterator it = _clientsReady.begin();
	while (it != _clientsReady.end()){
		nicknames.push_back(((*it)->getNickname()));
		it++;
	}
	return (nicknames);
}

Channel *Server::getChannel(const std::string &name)
{
	std::vector<Channel *>::iterator it;
	for (it = _channels.begin(); it != _channels.end(); it++)
		if (it.operator*()->getName() == name)
			return it.operator*();

	return NULL;
}
