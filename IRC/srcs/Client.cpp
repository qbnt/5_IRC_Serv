/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:18:07 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/01 07:14:46 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

//--------------------------------Fonctions-----------------------------------||

bool	Client::isConnected() const {

	if (getNickname().empty() || getUsername().empty() || !isPasswordOK())
		return false;
	return true;
}

void	Client::linkSetMsg() const {

	// * Msg d'arrivé à afficher sur le serveur
}

void	Client::sendMsg(const std::string & msg) const {

	// * Fonction de reception de message Serveur
}

void	Client::joinChan(Channel *chan) {

	chan->addUser(this);
	if (chan->getNbrUsr() == 1) {
		chan->setAdmin(this);
		chan->setNewOp(this);
	}
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

Client::Client(int socket, Server* serv, std::string const & pseudo)
				: _socket(socket), _serv(serv), _nickname(pseudo), _passwordOk(false) {

	std::clog << "Client " << pseudo << "crée avec le socket -> " << socket << std::endl;
}

Client::Client(Server * serv, int const socket, std::string const ip, int const port)
				: _serv(serv), _socket(socket), _ip(ip), _port(port), _passwordOk(false) {

	std::clog << "Client " << "crée avec le socket -> " << socket << std::endl;
}


Client::~Client(){
	// TODO: Ajouter la libération de mémoire si besoin
}
