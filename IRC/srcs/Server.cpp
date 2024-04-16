/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:48:12 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/16 13:35:44 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(){
	_socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	_time = time(NULL);
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