/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:49 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/08 13:46:25 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

//----------------------------------------------------------------------------||

NickCommand::NickCommand(Server *server, bool auth) : Command(server, auth) {}

NickCommand::~NickCommand() {}

void NickCommand::execute(Client *usr, std::vector<std::string> args) {

	if (args.empty() || args[0].empty()) {
		usr->sendMsg(ERR_NONICKNAMEGIVEN(usr->getPref()));
		return;
	}

	std::string nickname = args[0];
	if (_server->getClient(nickname)) {
		usr->sendMsg(ERR_NICKNAMEINUSE(usr->getPref(), nickname));
		return;
	}

	usr->setNickname(nickname);
	usr->linkSetMsg();
}
