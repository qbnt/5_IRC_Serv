/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:20:32 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/06 12:24:14 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

PingCommand::PingCommand(Server* serv): Command(serv){
}

PingCommand::~PingCommand(){}

void	PingCommand::execute(Client* client, std::vector<std::string> arguments){
	if (arguments.empty()){
		client->sendMsg(ERR_NEEDMOREPARAMS(client->getPref(), "PING"));
		return ;
	}
	client->send(RPL_PING(client->getPref(), arguments.at(0)));
}