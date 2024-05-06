/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:24:16 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/06 13:11:15 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

PrivMsgCommand::PrivMsgCommand(Server* serv): Command(serv){}

PrivMsgCommand::~PrivMsgCommand(){}

void	PrivMsgCommand::execute(Client* client, std::vector<std::string> arguments){
	if (arguments.empty() || arguments[0].empty() || arguments[1].empty()){
		client->sendMsg(ERR_NEEDMOREPARAMS(client->getPref(), "PRIVMSG"));
	}
	std::string	target = arguments[0];
	std::string	message;
	for (std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); it++){
		message.append(*it + " ");
	}
	message = message.at(0) == ':' ? message.substr(1) : message;
	if (target.at(0) == '#'){
		std::vector<Channel*>				client_channels = client->getUsrChan();
		std::vector<Channel*>::iterator		it = client_channels.begin();

		Channel*	chan;
		std::string chan_name;
		while (it != client_channels.end()){
			chan = it.operator*();
			if (chan->getName() == target)
				break;
			it++;
		}
		if (it == client_channels.end()){
			_server->broadcast(ERR_NOTONCHANNEL(client->getNickname(), target));
			return ;
		}
		chan->diff(RPL_PRIVMSG(client->getPref(), target, message));
	}
	Client*	dest = _server->getClient(target);
	if (!dest){
		client->sendMsg(ERR_NOSUCHCHANNEL(client->getNickname(), target));
		return ;
	}
	dest->send(RPL_PRIVMSG(client->getPref(), target, message));
}