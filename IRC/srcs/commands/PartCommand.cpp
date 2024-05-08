/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:59 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/08 13:57:28 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

PartCommand::PartCommand(Server *server) : Command(server) {}

PartCommand::~PartCommand() {}

void PartCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.empty())
	{
		client->sendMsg(ERR_NEEDMOREPARAMS(client->getNickname(), "PART"));
		return;
	}

	std::string name = arguments[0];
	std::string reason = "";

	// Assemble reason
	if (arguments.size() >= 2)
		for (std::vector<std::string>::iterator it = arguments.begin() + 1; it != arguments.end(); it++)
			reason.append(*it + " ");
	// remove first :
	if (reason[0] == ':')
		reason = reason.substr(1, reason.size());
	// remove last space
	if (reason[reason.size() - 1] == ' ')
		reason = reason.substr(0, reason.size() - 1);

	Channel *channel = _server->getChannel(name);
	if (!channel)
	{
		client->sendMsg(ERR_NOSUCHCHANNEL(client->getNickname(), name));
		return;
	}

	std::vector<Channel *> chans = client->getUsrChan();
	std::vector<Channel *>:: iterator it = chans.begin();

	Channel *chan;
	while (it != chans.end())
	{
		chan = it.operator*();
		if (chan->getName() == name)
			break ;
		++it;
	}
	if (it == chans.end())
	{
		client->send(ERR_NOTONCHANNEL(client->getNickname(), name));
	 	return;
	}

	client->leaveChan(chan, 0, reason);
}
