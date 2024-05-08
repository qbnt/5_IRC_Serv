/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:15:32 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/06 15:05:22 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

QuitCommand::QuitCommand(Server* serv, bool auth): Command(serv, auth){}

QuitCommand::~QuitCommand(){}

void	QuitCommand::execute(Client* client, std::vector<std::string> arguments){
	std::string reason = arguments.empty() ? "Leaving..." : arguments.at(0);
	reason = reason.at(0) == ':' ? reason.substr(1) : reason;
	client->send(RPL_QUIT(client->getPref(), reason));
	this->_server->deleteClient(client->getClientSocket());
}