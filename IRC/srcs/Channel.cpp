/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:56:02 by qbanet            #+#    #+#             */
/*   Updated: 2024/04/18 16:32:31 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

//----------------------------------------------------------------------------||

Channel::Channel(std::string const &nm, std::string const &tpc, std::string const &pw, Client *adm, Server *serv)
				: _name(nm), _topic(tpc), _password(pw), _admin(adm), _serv(serv) {


}

Channel::~Channel() {

}