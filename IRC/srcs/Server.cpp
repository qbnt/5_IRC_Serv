/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:48:12 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/18 10:08:57 by mescobar         ###   ########.fr       */
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
		this->_clientsFd[i + 1].fd = this->_clientsReady[i]->getClientFd();
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
	this->addclient();
	char str_ipv6_addr[INET6_ADDRSTRLEN];
	std::cout << "server: connection received from: " << inet_ntop(AF_INET6, &address, str_ipv6_addr, INET6_ADDRSTRLEN) \
		<< "port: " << ntohs(address.sin6_port) << std::endl;
}

void	Server::_waitForConnections(){
	int	socketActivity = poll(this->_clientsFd, this->_clientsReady.size() + 1, -1);
	if (socketActivity < 0)
		std::cout << "Error: No socket activity." << std::endl;

	for (size_t i = 0; i < _clientsReady.size(); i++){
		//if revents == 0 that means that there is no activity
		if (this->_clientsFd[i].revents == 0)
			continue;
		if (this->_clientsFd[i].fd == this->_socketFd) //if there is some activity, we'll try to connect to it
			this->_acceptConnection();
		//we take the message from the last client
		Client*	client = this->_clientsReady[i - 1];
		this->clientMessage();
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
	if (bind(this->_socketFd, (struct sockaddr*)&adress, sizeof(adress)) < 0)
		throw(Bind());

	std::cout << "ircserv connect on port: " << this->_port << std::endl;

	//creation of clientFd vector and listen loop
	this->_createClientFds();
	if (listen(_socketFd, 32) < 0)
		throw(Listen());
	while (1){
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

Server::Server(int port, std::string const& password): _port(port), _password(password){
	_serverName = DEFAULT_SERVER_NAME;
	_socketFd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	_clientsFd = NULL;;
	this->IRC();
}

Server::Server(){
}

Server::Server(Server const& cp){
	*this = cp;
}

Server::~Server(){
	close(_socketFd);
}

Server& Server::operator=(Server const& cp){
	if (this != &cp){
		_socketFd = cp._socketFd;
	}
	return (*this);
}