/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:38 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/06 12:58:01 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

//----------------------------------------------------------------------------||

JoinCommand::JoinCommand(Server *srv) : Command(srv) {}

JoinCommand::~JoinCommand() {}

void	JoinCommand::execute(Client *usr, std::vector<std::string> args) {

	if (args.empty()) {
		usr->sendMsg(ERR_NEEDMOREPARAMS(usr->getNickname(), "JOIN"));
		return ;
	}

	std::string	chanName = args[0];
	std::string password = args.size() > 1 ? args[1] : "";

	Channel *chan = _server->getChannel(chanName);
	if (!chan)
		chan = _server->createChannel(chanName, password, usr);
	if (chan->getInvMode()) {
		usr->sendMsg(ERR_INVITEONLYCHAN(usr->getNickname(), chanName));
		return ;
	}
	if (chan->isInChan(usr))
		return ;

	if (chan->getMaxUsr() > 0 && chan->getClients().size() >= chan->getMaxUsr()) {
		usr->sendMsg(ERR_CHANNELISFULL(usr->getNickname(), chanName));
		return ;
	}
	if (chan->getPassword() != password) {
		usr->sendMsg(ERR_BADCHANNELKEY(usr->getNickname(), chanName));
		return ;
	}
	if (chan->getInvMode() == true) {
		usr->sendMsg(ERR_INVITEONLYCHAN(usr->getNickname(), chanName));
		return ;
	}

	usr->joinChan(chan);
}