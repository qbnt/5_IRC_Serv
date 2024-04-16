/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:48:12 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/16 09:53:06 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(){
	//something
}

Server::Server(Server const& cp){
	*this = cp;
}

Server::~Server(){
	//something
}

Server& Server::operator=(Server const& cp){
	if (this != &cp){
		//something
	}
	return (*this);
}