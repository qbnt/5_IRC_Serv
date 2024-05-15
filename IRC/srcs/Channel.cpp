/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:56:02 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/15 20:47:58 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

//--------------------------------Fonctions-----------------------------------||

void	Channel::diff(std::string const & msg) {

	this->_serv->broadcastChannel(msg, this);
}

void Channel::diff(const std::string &message, Client *exclude) {

	this->_serv->broadcastChannel(message, exclude->getClientSocket(), this);
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
		_op.erase(this->_op.begin() + this->_clientIndex(_op, usr));
	if (!_clients.empty())
		_clients.erase(this->_clients.begin() + this->_clientIndex(_clients, usr));
	usr->leaveChan(this, 1, reason);

	if (_clients.empty()) {
		return;
	}

	if (_admin == usr)
		_admin = _clients.begin().operator*();
}

void	Channel::addOp(Client *newOp) {

	_op.push_back(newOp);
}

void	Channel::removeOp(Client *usr) {

	std::vector<Client *>::iterator it = _op.begin();
	while (it != _op.end() || (*it) != usr) {
		it ++;
	}
	_op.erase(it);
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

	std::vector<Client *>::iterator it = _clients.begin();

	while (it != _clients.end())
	{
		if (*it == usr)
			return true;
		it++;
	}
	return false;

}

bool	Channel::isOp(Client const * usr) {

	std::vector<Client *> opers_chan = this->getOp();
	std::vector<Client *>:: iterator it_oper = opers_chan.begin();

	while (it_oper != opers_chan.end())
	{
		Client *oper = it_oper.operator*();
		if (oper == usr)
			return true;
		++it_oper;
	}
	if (it_oper == opers_chan.end())
		return false;
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

unsigned long Channel::clientIndex(std::vector<Client *> clients, Client *usr)
{
	unsigned long i = 0;
	std::vector<Client *>::iterator it = clients.begin();

	while (it != clients.end())
	{
		if (*it == usr)
			return i;
		it++;
		i++;
	}
	return 0;
}

unsigned long Channel::_clientIndex(std::vector<Client *> clients, Client *client)
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

Client *	Channel::getClient(std::string const &pseudo) {

	for (ChanIter it = _clients.begin(); it != _clients.end(); it ++) {
		if ((*it)->getNickname() == pseudo)
			return *it;
	}
	return NULL;
}

std::vector<std::string>	Channel::getNickNames()
{
	std::vector<std::string> nicknames;
	std::vector<Client *>::iterator it = _clients.begin();

	while (it != _clients.end())
	{
		Client *usr = it.operator*();
		nicknames.push_back((_admin == usr ? "@" : "") + (*it)->getNickname());
		it++;
	}
	return nicknames;
}


//---------------------------Construct & Destructs----------------------------||

Channel::Channel(std::string const &nm, std::string const &pw, Client *adm, Server *serv)
				: _name(nm), _maxUsr(42), _inviteMode(false), _password(pw), _serv(serv), _admin(adm) {}

Channel::~Channel() {
	// TODO: Ajouter la libération de mémoire si besoin
}
