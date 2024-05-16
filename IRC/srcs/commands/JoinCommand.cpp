/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:38 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/16 13:56:02 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

//----------------------------------------------------------------------------||

JoinCommand::JoinCommand(Server *srv) : Command(srv) {}

JoinCommand::~JoinCommand() {}

void	JoinCommand::execute(Client *usr, std::vector<std::string> args) {

	if (args.size() < 1) {
		usr->sendMsg(ERR_NEEDMOREPARAMS(usr->getNickname(), "JOIN"));
		return;
	}

	std::string name = args[0];
	std::string password = args.size() > 1 ? args[1] : "";

	if (name.at(0) == '#') {
		Channel *channel = _server->getChannel(name);
		if (!channel)
			channel = _server->createChannel(name, password, usr);

		if (channel->getInvMode())
		{
			usr->sendMsg(ERR_INVITEONLYCHAN(usr->getNickname(), channel->getName()));
			return ;
		}

		std::vector<Client *> clients = channel->getClients();
		std::vector<Client *>::iterator it;

		it = clients.begin();
		while (it != clients.end())
		{
			Client *cl = it.operator*();
			if (cl == usr)
				return ;
			it++;
		}

		if (channel->getMaxUsr() > 0 && channel->getClients().size() >= channel->getMaxUsr())
		{
			usr->sendMsg(ERR_CHANNELISFULL(usr->getNickname(), channel->getName()));
			return;
		}

		if (channel->getPassword() != password)
		{
			usr->sendMsg(ERR_BADCHANNELKEY(usr->getNickname(), channel->getName()));
			return;
		}

		if (channel->getInvMode() == 1)
		{
			usr->sendMsg(ERR_INVITONLYCHAN(usr->getNickname(), channel->getName()));
			return;
		}
		usr->joinChan(channel);
	} else {
		Channel *privmsg = _server->getChannel(name);
		if (!privmsg)
			return ;
		usr->joinChan(privmsg);
	}

}