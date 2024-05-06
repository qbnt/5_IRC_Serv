/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:48:12 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/06 10:01:41 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_createClientFds(void){
	if (this->_clientsFd)
		delete [] this->_clientsFd;
	this->_clientsFd = new struct pollfd[this->_clientsReady.size() + 1];
	this->_clientsFd[0].fd = this->_socketFd;
	this->_clientsFd[0].events = POLLIN;
	for (size_t i = 0; i < this->_clientsReady.size(); i++){
		this->_clientsFd[i + 1].fd = this->_clientsReady[i]->getClientSocket();
		this->_clientsFd[i + 1].events = POLLIN;
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
	std::cout << "server: connection received from: " << inet_ntop(AF_INET6, &address, str_ipv6_addr, INET6_ADDRSTRLEN) \
		<< "port: " << ntohs(address.sin6_port) << std::endl;
}

void	Server::_parsMessage(std::string msg, Client* client){
	std::vector<std::string> cmd;
	if (msg.find('\n') != 0)
		cmd = ft_split(msg, 'c');
	else
		cmd.push_back(msg);
	for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end(); it++){
		_commands->handle(client, *it);
	}
}

void	Server::_clientMessage(Client*	client){
	char buff[BUFFER_SIZE + 1];
	while (true){
		int	res = recv(client->getClientSocket(), buff, BUFFER_SIZE + 1, 0);
		if (res < 0){
			std::cout << "Error: recv() from client: " << client->getClientSocket();
			this->deleteClient(client->getClientSocket());
			break;
		}
		if (!res){
			this->deleteClient(client->getClientSocket());
			break;
		}
		else{
			buff[res] = '\0';
			std::string msg = buff;
			_parsMessage(msg, client);
		}
	}
}

void	Server::_waitForConnections(){
	int	socketActivity = poll(this->_clientsFd, this->_clientsReady.size() + 1, -1);
	if (socketActivity < 0)
		std::cout << "Error: No socket activity." << std::endl;

	for (size_t i = 0; i < _clientsReady.size(); i++){
		//if revents == 0 that means that there is no activity
		if (this->_clientsFd[i].revents == 0)
			continue;
		if (this->_clientsFd[i].fd == this->_socketFd) //if there is some activity, we treat it as a connection
			this->_acceptConnection();
		//we take the message from the last client
		Client*	client = this->_clientsReady[i - 1];
		this->_clientMessage(client);
	}
}

void	Server::IRC(){
	int 					opt = 1;
	struct sockaddr_in6		adress;
	int						adresslen = sizeof(adress);

	//creation of socket
	if (_socketFd == SOCKET_ERROR)
		throw(Socket());
	if (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt) < 0))
		throw(SocketOptions());

	//type of socket and bind to the port
	adress.sin6_family = AF_INET6;
	adress.sin6_addr = in6addr_any;
	adress.sin6_port = htons(this->_port);
	if (bind(this->_socketFd, (struct sockaddr*)&adress, adresslen) < 0)
		throw(Bind());

	std::cout << "ircserv connected on port: " << this->_port << std::endl;

	//creation of clientFd vector and listen loop
	this->_createClientFds();
	if (listen(_socketFd, 32) < 0)
		throw(Listen());
	while (true){
		std::cout << "Server waiting for connections." << std::endl;
		this->_waitForConnections();
		usleep(100);
		std::cout << "Server waiting for connections.." << std::endl;
		this->_waitForConnections();
		usleep(100);
		std::cout << "Server waiting for connections..." << std::endl;
		this->_waitForConnections();
		usleep(100);
	}
}

void	Server::addClient(int const socket, std::string const ip, int const port){
	this->_clientsReady.push_back(new Client(this, socket, ip, port));
	this->_createClientFds();
}

Server::Server(int port, std::string const& password): _port(port), _password(password){
	_serverName = DEFAULT_SERVER_NAME;
	_socketFd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	_clientsFd = NULL;;
	_startTime = timeString();
	this->IRC();
}

Server::~Server(){
	// TODO: Ajouter la libération de mémoire si besoin;
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