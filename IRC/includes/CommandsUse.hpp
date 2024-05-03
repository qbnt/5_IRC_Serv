#pragma once
#include "IRC.hpp"

class Command;
class Client;
class Server;

class CommandsUse{
	private:
		Server*							_server;
		std::map<std::string, Command*>	_comMap;
	public:
		CommandsUse();
		CommandsUse(Server*);
		~CommandsUse();

		void	handle(Client*, std::string const&);
};