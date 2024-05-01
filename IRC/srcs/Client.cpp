/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:18:07 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/01 17:11:20 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

//--------------------------------Fonctions-----------------------------------||

bool const	Client::isOk() const {

	if (getNickname().empty() || getUsername().empty() || getRealname().empty() || !isPasswordOK())
		return false;
	return true;
}

void	Client::send(const std::string & msg) const {

	_serv->send(msg, getClientSocket());
}

void	Client::sendMsg(const std::string & msg) const {

	this->send(":" + _serv->getServerName() + " " + msg);
}

std::string const	Client::getPref() const {

	if (getNickname().empty())
		return "*";
	return _nickname + (_username.empty() ? "" : "!" + _username) + (_hostname.empty() ? "" : "@" + _hostname);
}

void	Client::linkSetMsg() const {

	if(!isOk())
		return ;
	sendMsg(RPL_WELCOME(getNickname(), getHostname()));
	sendMsg(RPL_YOURHOST(getNickname(), _serv->getServerName(), VERSION));
	sendMsg(RPL_CREATED(getNickname(), _serv->_getStartTime()));
	sendMsg(RPL_MYINFO(getNickname(), _serv->getServerName(), VERSION, USERMODES, CHANNELMODES));

	sendMsg(RPL_MOTDSTART(getNickname(), _serv->getServerName()));
	sendMsg(RPL_MOTD(getNickname(), " :- #####################################"));
	sendMsg(RPL_MOTD(getNickname(), " :- # Bienvenue sur notre serveur IRC ! #"));
	sendMsg(RPL_MOTD(getNickname(), " :- #####################################"));
	sendMsg(RPL_ENDOFMOTD(getNickname()));
}

void	Client::joinChan(Channel *chan) {

	chan->addUser(this);
	_usrChan.push_back(chan);
	if (chan->getNbrUsr() == 1) {
		chan->setAdmin(this);
		chan->setNewOp(this);
	}

	std::string users;
	std::vector<std::string> nicknames = chan->getAllNickname();
	for (std::vector<std::string>::iterator it = nicknames.begin(); it != nicknames.end(); it ++) {
		users += (*it + " ");
	}

	chan->diff(RPL_JOIN(getPref(), chan->getName()));

	sendMsg(RPL_NOTOPIC(getNickname(), chan->getName()));
	sendMsg(RPL_NAMREPLY(getNickname(), chan->getName(), users));
	sendMsg(RPL_ENDOFNAMES(getNickname(), chan->getName()));
}

void	Client::leaveChan(Channel * chan, bool kicked, std::string const& reason) {

	if (kicked)
		chan->removeUser(this, reason);
	for (ChanVecIt it = _usrChan.begin(); it != _usrChan.end(); ++it) {
        if (*it == chan) {
            _usrChan.erase(it);
            break;
        }
    }
}

//----------------------------Constructs & Destruct---------------------------||

Client::Client(Server * serv, int const socket, std::string const &ip, int const port)
				: _serv(serv), _socket(socket), _hostname(ip), _port(port), _passwordOk(false) {

	std::clog << "Client " << "crée avec le socket -> " << socket << std::endl;
}


Client::~Client(){
	// TODO: Ajouter la libération de mémoire si besoin
}
