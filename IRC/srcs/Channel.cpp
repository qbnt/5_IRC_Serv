/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:56:02 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/03 12:27:06 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

//--------------------------------Fonctions-----------------------------------||

void	Channel::diff(std::string const & msg) {

	ChanIter it;
	for(it = _clients.begin(); it != _clients.end(); it++) {
		(*it)->send(msg);
	}
}

void	Channel::addUser(Client *usr) {

	_clients.push_back(usr);
}

void	Channel::removeUser(Client *usr, std::string reason) {

	std::string clientPrefix = usr->getPref();

	if (reason.empty())
		this->diff(RPL_PART(clientPrefix, this->getName()));
	else
		this->diff(RPL_PART_REASON(clientPrefix, this->getName(), reason));
	reason.clear();

	if (!_op.empty())
		_op.erase(this->_op.begin() + this->clientIndex(_op, usr));
	if (!_clients.empty())
		_clients.erase(this->_clients.begin() + this->clientIndex(_clients, usr));
	usr->leaveChan(this, false, reason);

	if (_clients.empty())
		return;

	if (_admin == usr)
		_admin = _clients.begin().operator*();
}

void	Channel::addOp(Client *newOp) {

	_op.push_back(newOp);
}

void	Channel::removeOp(Client *origin, Client *target, std::string reason) {

	diff(RPL_KICK(origin->getNickname(), _name, target->getNickname(), reason));
	reason.clear();
	removeUser(target, reason);
}

void	Channel::invit(Client *origin, Client *target) {

	origin->sendMsg(RPL_INVITING(origin->getNickname(), target->getNickname(), _name));
	target->send(RPL_INVITE(origin->getPref(), target->getNickname(), _name));
	target->joinChan(this);
}

void	Channel::kick(Client *origin, Client *target, std::string reason) {

	diff(RPL_KICK(origin->getPref(), _name, target->getNickname(), reason));
	reason.clear();
	removeUser(target, reason);
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

unsigned long Channel::clientIndex(std::vector<Client *> clients, Client *client)
{
	unsigned long i = 0;
	std::vector<Client *>::iterator it = clients.begin();

	while (it != clients.end())
	{
		if (*it == client)
			return i;
		it++;
		i++;
	}
	return 0;
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

Channel::Channel(std::string const &nm, std::string const &pw, Client *adm, Server *serv)
				: _name(nm), _password(pw), _admin(adm), _serv(serv), _maxUsr(42) {}

Channel::~Channel() {
	// TODO: Ajouter la libération de mémoire si besoin
}
