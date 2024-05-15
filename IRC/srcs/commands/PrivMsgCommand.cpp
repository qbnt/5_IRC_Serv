/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:24:16 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/15 20:01:23 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

PrivMsgCommand::PrivMsgCommand(Server* serv): Command(serv){}

PrivMsgCommand::~PrivMsgCommand(){}

void	PrivMsgCommand::execute(Client* client, std::vector<std::string> arguments){

	if (arguments.size() < 2 || arguments[0].empty() || arguments[1].empty()) {
		client->sendMsg(ERR_NEEDMOREPARAMS(client->getNickname(), "PRIVMSG"));
		return;
	}

	std::string target = arguments.at(0);
	std::string message;

	for (std::vector<std::string>::iterator it = arguments.begin() + 1; it != arguments.end(); it++) {
		message.append(*it + " ");
	}

	message = message.at(0) == ':' ? message.substr(1) : message;

	if (target.at(0) == '#') {

		std::vector<Channel *> client_chans = client->getUsrChan();
		std::vector<Channel *>:: iterator it = client_chans.begin();

		Channel *chan;
		std::string chan_name;
		while (it != client_chans.end())
		{
			chan = it.operator*();
			if (chan->getName() == target)
				break ;
			++it;
		}
		if (it == client_chans.end())
		{
			_server->broadcast(ERR_NOTONCHANNEL(client->getNickname(), target));
			return;
		}

		chan->diff(RPL_PRIVMSG(client->getPref(), target, message), client);
		return;
	}

	Client *dest = _server->getClient(target);
	if (!dest)
	{
		client->sendMsg(ERR_NOSUCHNICK(client->getNickname(), target));
		return;
	}

	dest->send(RPL_PRIVMSG(client->getPref(), target, message));

}