/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoCommand.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:10:07 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/14 12:24:29 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

WhoCommand::WhoCommand(Server* serv): Command(serv){}

WhoCommand::~WhoCommand(){}

void	WhoCommand::execute(Client* client, std::vector<std::string> arguments){
	std::string channelName = "*";

	if (arguments.empty()){
		std::vector<Client*> clients = _server->getClientsVector();
		for (long unsigned int i = 0; i < clients.size(); i++){
			client->sendMsg(RPL_WHOREPLY(client->getNickname(), channelName, clients[i]->getUsername(), clients[i]->getHostname(), this->_server->getServerName(), clients[i]->getNickname(), clients[i]->getRealname()));
		}
	}
	else if (arguments.size() == 1){
		if (arguments[0].at(0) == '#'){
			channelName = arguments[0];
			Channel*	channel = _server->getChannel(channelName);
			if (channel){
				std::vector<Client*>clients = channel->getClients();
				for (unsigned int i = 0; i < clients.size(); i++){
					client->sendMsg(RPL_WHOREPLY(client->getNickname(), channelName, clients[i]->getUsername(), clients[i]->getHostname(), this->_server->getServerName(), clients[i]->getNickname(), clients[i]->getRealname()));
				}
			}
		}
	}
	client->sendMsg(RPL_ENDOFWHO(client->getNickname(), channelName));
}