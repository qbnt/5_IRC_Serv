/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:18:07 by qbanet            #+#    #+#             */
/*   Updated: 2024/04/19 16:27:09 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

//--------------------------------Fonctions-----------------------------------||

void	Client::linkSetMsg() const {

	// * Msg d'arrivé à afficher sur le serveur
}

void	Client::sendMsg(const std::string & msg) const {

	// * Fonction de reception de message Serveur
}

void	Client::joinChan(Channel *chan) {

	chan->addUser(this);
	_usrChan.push_back(chan);
	if (chan->getNbrUsr() == 1) {
		chan->setAdmin(this);
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
				: _socket(socket), _serv(serv), _pseudo(pseudo), _passwordOk(false) {

	std::clog << "Client " << pseudo << "crée avec le socket -> " << socket << std::endl;
}

Client::Client(Server * serv, int const socket, std::string const ip, int const port)
				: _serv(serv), _socket(socket), _ip(ip), _port(port), _passwordOk(false) {

	std::clog << "Client " << "crée avec le socket -> " << socket << std::endl;
}


Client::~Client(){
	// TODO: Ajouter la libération de mémoire si besoin
}
