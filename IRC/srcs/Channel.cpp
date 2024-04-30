/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:56:02 by qbanet            #+#    #+#             */
/*   Updated: 2024/04/23 11:21:50 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

//--------------------------------Fonctions-----------------------------------||

void	Channel::addUser(Client *usr) {

	_clients.push_back(usr);
	usr->joinChan(this);
}

void	Channel::removeUser(Client *usr, std::string const& reason) {

	usr->leaveChan(this, false, reason);
}

bool	Channel::isInChan(Client const * usr) {

	for (ChanIter it = _clients.begin(); it != _clients.end(); it ++) {
		if (*it == usr)
			return true;
	}
	return false;
}

unsigned int	Channel::getNbrUsr() {
	return _clients.size();
}

std::vector<std::string> const	Channel::getAllNickname() {

	std::vector<std::string>	allNickname;

	for (ChanIter it = _clients.begin(); it != _clients.end(); it++) {
		allNickname.push_back((*it)->getNickname());
	}
	return allNickname;
}

//---------------------------Getteurs & Setteurs------------------------------||

Client const *	Channel::getClient(std::string const &pseudo) {

	for (ChanIter it = _clients.begin(); it != _clients.end(); it ++) {
		if ((*it)->getNickname() == pseudo)
			return *it;
	}
	return NULL;
}

//---------------------------Construct & Destructs----------------------------||

Channel::Channel(std::string const &nm, std::string const &tpc, std::string const &pw, Client *adm, Server *serv)
				: _name(nm), _topic(tpc), _password(pw), _admin(adm), _serv(serv), _maxUsr(42) {}

Channel::~Channel() {
	// TODO: Ajouter la libération de mémoire si besoin
}
