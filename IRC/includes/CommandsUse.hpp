#pragma once
#include "IRC.hpp"

class Commands;
class Client;
class Server;

class CommandsUse{
	private:
		Server*							_server;
		std::map<std::string, Commands *>	_comMap;
	public:
		CommandsUse(Server*	server);
		~CommandsUse();
};