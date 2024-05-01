/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:56:02 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/01 17:30:56 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

//--------------------------------Fonctions-----------------------------------||

void	Channel::addUser(Client *usr) {

	
}

void	Channel::removeUser(Client *usr, std::string const& reason) {

	usr->leaveChan(this, false, reason);
}

void	Channel::removeOp(Client const *usr) {

	ChanIter it;
	for (it = _op.begin(); it != _op.end() || *it != usr; it++);
	if (it != _op.end())
		_op.erase(it);
}

void	Channel::diff(std::string const & msg) {

	ChanIter it;
	for(it = _clients.begin(); it != _clients.end(); it++) {
		(*it)->send(msg);
	}
}

bool	Channel::isInChan(Client const * usr) {

	for (ChanIter it = _clients.begin(); it != _clients.end(); it ++) {
		if (*it == usr)
			return true;
	}
	return false;
}

bool	Channel::isOp(Client const * usr) {

	ChanIter it;
	for (it = _op.begin(); it != _op.end(); it++) {
		Client *op = it.operator*();
		if (op == usr)
			return true;
	}
	return false;
}

unsigned int	Channel::getNbrUsr() {
	return _clients.size();
}

std::vector<std::string>	Channel::getAllNickname() {

	std::vector<std::string>	allNickname;
	ChanIter it;

	for (it = _clients.begin(); it != _clients.end(); it++) {
		Client *cli = it.operator*();
		allNickname.push_back((_admin == cli ? "@" : "") + (*it)->getNickname());
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
