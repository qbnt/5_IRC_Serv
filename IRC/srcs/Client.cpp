/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:51:13 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/16 09:52:28 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(){
	//something
}

Client::Client(Client const& cp){
	*this = cp;
}

Client::~Client(){
	//something
}

Client&	Client::operator=(Client const& cp){
	if (this != &cp){
		//something
	}
	return (*this);
}