/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:43 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/08 13:30:33 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

//----------------------------------------------------------------------------||

ListCommand::ListCommand(Server *srv) : Command(srv) {}

ListCommand::~ListCommand() {}

static bool isInChannelsList(Channel *channel, std::vector<std::string> channelNames) {

	for (std::vector<std::string>::iterator it = channelNames.begin(); it != channelNames.end(); it++)
	{
		if (channel->getName() == *it)
			return true;
	}
	return false;
}

static std::string intToString(int num)
{
	std::ostringstream ss;
	ss << num;
	return (ss.str());
}

void ListCommand::execute(Client *usr, std::vector<std::string> args) {

	std::vector<Channel *> chans = _server->getChannels();
	std::vector<std::string> channelNames;

	if (args.size() > 0)
		channelNames = ft_split(args[0], ',');

	for(unsigned long i=0; i < chans.size(); i++) {
		if (args.empty() || isInChannelsList(chans[i], channelNames))
			usr->sendMsg(RPL_LIST(usr->getNickname(), chans[i]->getName(), intToString(chans[i]->getClients().size()), "No topic is set"));
	}

	usr->sendMsg(RPL_LISTEND(usr->getNickname()));
}