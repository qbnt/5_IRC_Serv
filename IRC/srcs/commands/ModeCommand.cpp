/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:47 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/16 13:08:16 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

//----------------------------------------------------------------------------||

ModeCommand::ModeCommand(Server *srv) : Command(srv) {}

ModeCommand::~ModeCommand() {}

void ModeCommand::execute(Client *usr, std::vector<std::string> args)
{
	if (args.size() < 2 || args[0].empty() || args[1].empty()) {
		return;
	}

	std::string target = args.at(0);

	Channel *channel = _server->getChannel(target);
	if (!channel)
	{
		usr->sendMsg(ERR_NOSUCHCHANNEL(usr->getNickname(), target));
		return;
	}

	// check if admin or chanop
	if (channel->getAdmin() != usr && !channel->isOp(usr))
	{
		usr->sendMsg(ERR_CHANOPRIVSNEEDED(usr->getNickname(), target));
		return;
	}

	int i = 0;
	int p = 2;
	char c;

	while ((c = args[1][i])) {

		char prevC = i > 0 ? args[1][i - 1] : '\0';
		bool active = prevC == '+';

		switch (c) {

			case 'i': {
				channel->setInvMode(active);
				channel->diff(RPL_MODE(usr->getPref(), channel->getName(), (active ? "+i" : "-i"), ""));
				break;
			}

			case 'l': {
				if (args.size() <= 2 && active) {
					usr->sendMsg(ERR_NEEDMOREPARAMS(usr->getNickname(), "MODE"));
					break;
				}
				channel->setMaxUsr(active ? std::atoi(args[p].c_str()) : 0);
				channel->diff(RPL_MODE(usr->getPref(), channel->getName(), (active ? "+l" : "-l"), (active ? args[p] : "")));
				p += active ? 1 : 0;
				break;
			}

			case 'k': {
				if (args.size() <= 2 && active) {
					usr->sendMsg(ERR_NEEDMOREPARAMS(usr->getNickname(), "MODE"));
					break;
				}
				channel->setPassword(active ? args[p] : "");
				channel->diff(RPL_MODE(usr->getPref(), channel->getName(), (active ? "+k" : "-k"), (active ? args[p] : "")));
				p += active ? 1 : 0;
				break;
			}

			case 'o': {
				if (args.size() <= 2) {
					usr->sendMsg(ERR_NEEDMOREPARAMS(usr->getNickname(), "MODE"));
					break;
				}
				Client *c_tar = channel->getClient(args[p]);
				if (!c_tar)
				{
					channel->diff(ERR_USERNOTINCHANNEL(usr->getNickname(), args[p], channel->getName()));
					return ;
				}
				if (active)
					channel->addOp(c_tar);
				else
					channel->removeOp(c_tar);
				channel->diff(RPL_MODE(usr->getPref(), channel->getName(), (active ? "+o" : "-o"), (c_tar->getNickname())));
				p += active ? 1 : 0;
				break;
			}

			default:
				break;
		}
		i++;
	}
}
