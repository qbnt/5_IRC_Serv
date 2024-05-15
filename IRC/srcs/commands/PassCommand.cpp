/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:49:17 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/15 19:42:57 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

PassCommand::PassCommand(Server* serv, bool auth): Command(serv, auth){}

PassCommand::~PassCommand(){}

void	PassCommand::execute(Client* client, std::vector<std::string> arguments){
	if (client->isOk()){
		client->sendMsg(ERR_ALREADYREGISTERED(client->getPref()));
		return ;
	}
	if (arguments.empty()){
		client->sendMsg(ERR_NEEDMOREPARAMS(client->getPref(), "PASS"));
		return ;
	}
	if (_server->getPassword() != arguments[0].substr(arguments[0][0] == ':' ? 1 : 0)){
		client->sendMsg(ERR_PASSWDMISMATCH(client->getPref()));
		return ;
	}
	client->setPasswordOk(true);
	client->linkSetMsg();
}