/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:40 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/08 13:13:46 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

//----------------------------------------------------------------------------||

KickCommand::KickCommand(Server *srv) : Command(srv) {}

KickCommand::~KickCommand() {}

void	KickCommand::execute(Client *usr, std::vector<std::string> args) {

	if (args.size() < 2) {
		usr->sendMsg(ERR_NEEDMOREPARAMS(usr->getNickname(), "KICK"));
		return ;
	}

	std::string chanName = args[0];
	std::string targetName = args[1];
	std::string reason = KICKDEFREASON;
	if (args.size() >= 3) {
		reason.clear();
		for (std::vector<std::string>::iterator it = args.begin() + 2; it != args.end(); it ++) {
			reason += ((*it) + " ");
		}
	}
	if (reason[0] == ':')
		reason = reason.substr(1, reason.size());
	if (reason[reason.size() - 1] == ' ')
		reason = reason.substr(0, reason.size() - 1);

	Channel *chan = _server->getChannel(chanName);
	if (!chan || !chan->isInChan(usr)) {
		usr->sendMsg(ERR_NOTONCHANNEL(usr->getNickname(), chanName));
		return ;
	}
	if (chan->getAdmin() != usr && !chan->isOp(usr)) {
		usr->sendMsg(ERR_CHANOPRIVSNEEDED(usr->getNickname(), chanName));
		return ;
	}

	Client *target = _server->getClient(targetName);
	if (!chan || !chan->isInChan(target)) {
		usr->sendMsg(ERR_USERNOTINCHANNEL(usr->getNickname(), target->getNickname(), chanName));
		return ;
	}
	chan->kick(usr, target, reason);
}