/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:48:12 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/17 08:38:33 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::IRC(){
	int 					opt = 1;
	struct sockaddr_in6		adress;
	int						adresslen = sizeof(adress);

	//creation of socket
	_socketFd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	if (_socketFd == SOCKET_ERROR)
		throw(Socket());
	if (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt) < 0))
		throw(SocketOptions());

	//type of socket
	adress.sin6_family = AF_INET6;
	adress.sin6_addr = in6addr_any;
	adress.sin6_port = DEFAULT_PORT;
	if (bind(this->_socketFd, (struct sockaddr*)&adress, sizeof(adress)) < 0)
		throw(Bind());

	std::cout << "ircserv connect on port: " << DEFAULT_PORT << std::endl;
	//listen
	if (listen(_socketFd, 32) < 0)
		throw(Listen());

	while (1){
		std::cout << "Server waiting for connections." << std::endl;
		waitForConnections();
		usleep(100);
		std::cout << "Server waiting for connections.." << std::endl;
		waitForConnections();
		usleep(100);
		std::cout << "Server waiting for connections..." << std::endl;
		waitForConnections();
		usleep(100);
	}
}

Server::Server(int port, std::string const& password): _port(port), _password(password){
	_serverName = DEFAULT_SERVER_NAME;
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