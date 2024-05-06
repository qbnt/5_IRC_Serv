/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:46:32 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/06 12:57:59 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"

class Client;
class CommandsUse;
class Server: public Error{
	private:

		int						_port;
		std::string				_password;
		std::string 			_serverName;
		int						_socketFd;
		std::vector<Client *>	_clientsReady;
		pollfd*					_clientsFd;
		CommandsUse*			_commands;
		std::string				_startTime;

		void	_createClientFds(void);
		void	_acceptConnection(void);
		void	_waitForConnections(void);
		void	_recvMessage(Client*);
		void	_parsMessage(std::string, Client*);
		void	_clientMessage(Client*);

		Server();
		Server(Server const&);
		Server&	operator=(Server const&);

	public:
		Server(int, std::string const& password);
		~Server();

		void	IRC();
		ssize_t	send(std::string, int) const;
		void	addClient(int const, std::string const, int const);
		void	deleteClient(int);
		void	broadcast(std::string const&) const;
		void	broadcast(std::string const&, int) const;

		//setters:
		void	setSocketFd(int cp)							{_socketFd = cp;};
		void	setPort(int cp)								{_port = cp;};
		void	setPassword(std::string cp)					{_password = cp;};
		void	setServerName(std::string cp)				{_serverName = cp;};
		void	setClientsVector(std::vector<Client*> cp)	{_clientsReady = cp;};
		void	setClientsFd(pollfd* cp)					{_clientsFd = cp;};
		void	setCommands(CommandsUse* cp)				{_commands = cp;};

		//getters:
		std::string				getStartTime()		const	{return (_startTime);};
		int						getSocketFd()		const	{return (_socketFd);};
		int						getPort()			const	{return (_port);};
		std::string				getPassword()		const	{return (_password);};
		std::string				getServerName() 	const	{return (_serverName);};
		std::vector<Client*>	getClientsVector()	const	{return (_clientsReady);};
		pollfd*					getClientsFd()		const	{return (_clientsFd);};
		CommandsUse*			getCommands()		const	{return (_commands);};
		Client*					getClient(std::string const& cl);
};