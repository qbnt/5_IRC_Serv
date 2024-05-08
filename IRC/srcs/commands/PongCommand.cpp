/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:57:39 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/08 14:58:24 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

PongCommand::PongCommand(Server *server) : Command(server) {}

PongCommand::~PongCommand() {}

void PongCommand::execute(Client *client, std::vector<std::string> arguments)
{

	if (arguments.empty()) {
		client->sendMsg(ERR_NEEDMOREPARAMS(client->getNickname(), "PONG"));
		return;
	}

	client->send(RPL_PING(client->getPref(), arguments.at(0)));
}
