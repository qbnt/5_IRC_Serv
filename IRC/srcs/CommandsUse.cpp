#include "CommandsUse.hpp"

CommandsUse::CommandsUse(){
}

CommandsUse::CommandsUse(Server* serv): _server(serv){
	_comMap["NoticeCommand"] = new NoticeCommand(serv);
	_comMap["PrivMsgComand"] = new PrivMsgCommand(serv);
	_comMap["PartCommand"] = new PartCommand(serv);
	_comMap["QuitCommand"] = new QuitCommand(serv, false);
	_comMap["JoinCommand"] = new JoinCommand(serv);
	_comMap["UserCommand"] = new UserCommand(serv, false);
	_comMap["NickCommand"] = new NickCommand(serv, false);
	_comMap["PassCommand"] = new PassCommand(serv, false);
	_comMap["KickCommand"] = new KickCommand(serv);
	_comMap["PingCommand"] = new PingCommand(serv);
	_comMap["PongCommand"] = new PongCommand(serv);
	_comMap["ModeCommand"] = new ModeCommand(serv);
	_comMap["InvitCommand"] = new InvitCommand(serv);
	_comMap["WhoCommand"] = new WhoCommand(serv);
	_comMap["ListCommand"] = new ListCommand(serv);
}

CommandsUse::~CommandsUse(){
	for (std::map<std::string, Command*>::iterator i = _comMap.begin(); i != _comMap.end(); i++){
		delete i->second;
		_comMap.erase(i);
	}
}

void	CommandsUse::handle(Client* client, std::string command){
}