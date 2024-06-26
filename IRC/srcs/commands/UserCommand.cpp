/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:06:19 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/14 12:20:29 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

UserCommand::UserCommand(Server* serv, bool auth): Command(serv, auth){}

UserCommand::~UserCommand(){}

void	UserCommand::execute(Client* client, std::vector<std::string> arguments){
	if (client->isOk()){
		client->sendMsg(ERR_ALREADYREGISTERED(client->getPref()));
		return ;
	}
	if (arguments.size() < 4){
		client->sendMsg(ERR_NEEDMOREPARAMS(client->getPref(), "USER"));
		return ;
	}
	client->setUsername(arguments[0]);
	client->setRealname(arguments[3].substr(1));
	client->linkSetMsg();
}