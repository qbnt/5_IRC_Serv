/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NoticeCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:53 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/08 13:55:38 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

NoticeCommand::NoticeCommand(Server *server) : Command(server) {};

NoticeCommand::~NoticeCommand() {};

void NoticeCommand::execute(Client *usr, std::vector<std::string> args) {

	if (args.size() < 2 || args[0].empty() || args[1].empty()) {
		usr->sendMsg(ERR_NEEDMOREPARAMS(usr->getNickname(), "NOTICE"));
		return ;
	}

	std::string target = args.at(0);
	std::string message;
	for (std::vector<std::string>::iterator it = args.begin() + 1; it != args.end(); it++) {
		message.append(*it + " ");
	}

	message = message.at(0) == ':' ? message.substr(1) : message;
	if (target.at(0) == '#') {
		std::vector<Channel *> client_chans = usr->getUsrChan();
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
			usr->sendMsg(ERR_NOTONCHANNEL(usr->getNickname(), chan_name));
			return;
		}

		chan->diff(RPL_NOTICE(usr->getPref(), target, message), usr);
		return;
	}

	Client *dest = _server->getClient(target);
	if (!dest)
	{
		usr->sendMsg(ERR_NOSUCHNICK(usr->getNickname(), target));
		return;
	}
	dest->send(RPL_NOTICE(usr->getPref(), target, message));
}
