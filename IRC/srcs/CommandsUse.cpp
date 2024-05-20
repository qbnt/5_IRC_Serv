#include "CommandsUse.hpp"

CommandsUse::CommandsUse(){}

CommandsUse::CommandsUse(Server* serv): _server(serv){
	_comMap["NOTICE"] 	= new NoticeCommand(serv);
	_comMap["PRIVMSG"]	= new PrivMsgCommand(serv);
	_comMap["PART"] 	= new PartCommand(serv);
	_comMap["QUIT"] 	= new QuitCommand(serv, false);
	_comMap["JOIN"] 	= new JoinCommand(serv);
	_comMap["USER"] 	= new UserCommand(serv, false);
	_comMap["NICK"] 	= new NickCommand(serv, false);
	_comMap["PASS"] 	= new PassCommand(serv, false);
	_comMap["KICK"] 	= new KickCommand(serv);
	_comMap["PING"] 	= new PingCommand(serv);
	_comMap["PONG"] 	= new PongCommand(serv);
	_comMap["MODE"] 	= new ModeCommand(serv);
	_comMap["INVITE"] 	= new InvitCommand(serv);
	_comMap["WHO"] 		= new WhoCommand(serv);
	_comMap["LIST"] 	= new ListCommand(serv);
}

CommandsUse::~CommandsUse(){
	for (std::map<std::string, Command*>::iterator i = _comMap.begin(); i != _comMap.end(); i++){
		delete i->second;
	}
}

void	CommandsUse::handle(Client* client, std::string const& message){
	std::stringstream	sstring(message);
	std::string			SplitCommand;

	std::clog << message << std::endl;
	while (std::getline(sstring, SplitCommand)) {

		SplitCommand = SplitCommand.substr(0, SplitCommand[SplitCommand.length() - 1] == '\r' ? SplitCommand.length() - 1 : SplitCommand.length());
		std::string	command = SplitCommand.substr(0, SplitCommand.find(' '));
		try {
			Command*	ccomand = _comMap.at(command);
			std::vector<std::string> commandArguments;
			std::stringstream	ss(SplitCommand.substr(command.length(), SplitCommand.length()));
			std::string buff;
			while (ss >> buff) {
				commandArguments.push_back(buff);
			}
			if (ccomand->getAuth() && !client->isOk()){
				client->sendMsg(ERR_NOTREGISTERED(client->getNickname()));
				return ;
			}
			ccomand->execute(client, commandArguments);
		}
		catch(const std::out_of_range &e){
			if (command != "CAP")
				client->sendMsg(ERR_UNKNOWNCOMMAND(client->getNickname(), command));
		}
	}
}
