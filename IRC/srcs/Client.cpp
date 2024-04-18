/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:51:13 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/18 14:02:05 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

//----------------------------------------------------------------------------||

void	Client::linkSetMsg() const {

	// * Msg d'arrivé à afficher sur le serveur
}

void	Client::joinChan(Channel *chan) {

	// ? Ajoute le client par une fonction de Channel
	_usrChan.push_back(chan);
	// ? Oppération de vérif entre Client et Channel
}

void	Client::leaveChan(Channel * chan, bool kicked, std::string const& reason) {

	if (kicked)
		// * Supp du user dans le Channel(this, reason);

	for (ChanVecIt it = _usrChan.begin(); it != _usrChan.end(); ++it) {
        if (*it == chan) {
            _usrChan.erase(it);
            break;
        }
    }
}

//----------------------------------------------------------------------------||

Client::Client(int socket, Server* serv, std::string const & pseudo)
				: _socket(socket), _serv(serv), _pseudo(pseudo), _isConnected(false) {

	std::clog << "Client " << pseudo << "crée avec le socket -> " << socket << std::endl;
}

Client::Client(Server * serv, int const socket, std::string const ip, int const port)
				: _serv(serv), _socket(socket), _ip(ip), _port(port), _isConnected(false) {

	std::clog << "Client " << "crée avec le socket -> " << socket << std::endl;
}


Client::~Client(){
	// TODO : Ajouter la livération de mémoire si besoin
}

//----------------------------------------------------------------------------||