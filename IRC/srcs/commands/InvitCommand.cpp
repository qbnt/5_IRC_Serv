/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InvitCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:43:41 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/06 12:31:56 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

//----------------------------------------------------------------------------||

InvitCommand::InvitCommand(Server* srv) : Command(srv) {}

InvitCommand::~InvitCommand() {}

void	InvitCommand::execute(Client *usr, std::vector<std::string> args) {

	if (args.size() < 2) {
		usr->sendMsg(ERR_NEEDMOREPARAMS(usr->getNickname(), "INVITE"));
		return ;
	}

	std::string target = args[0];
	std::string chanName = args[1];

	Channel* chan = _server->getChannel(chanName);
	if (!chan || !chan->getClient(usr->getNickname())) {
		usr->sendMsg(ERR_NOTONCHANNEL(usr->getNickname(), chan->getName()));
		return ;
	}
	if (chan->getInvMode() && usr != chan->getAdmin() && chan->isOp(usr)) {
		usr->sendMsg(ERR_CHANOPRIVSNEEDED(usr->getNickname(), chan->getName()));
		return ;
	}

	Client* targetUsr = _server->getClient(target);
	if (!targetUsr) {
		usr->sendMsg(ERR_NOSUCHNICK(usr->getNickname(), target));
		return ;
	}
	if (chan->isInChan(targetUsr)) {
		usr->sendMsg(ERR_USERONCHANNEL(usr->getNickname(), target, chanName));
		return ;
	}

	chan->invit(usr, targetUsr);
}