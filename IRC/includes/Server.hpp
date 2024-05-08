/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:46:32 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/08 15:02:11 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"

class Client;
class CommandsUse;
class Channel;
class Server: public Error{
	private:

		int						_port;
		std::string				_password;
		std::string 			_serverName;
		int						_socketFd;
		std::vector<Client *>	_clientsReady;
		std::vector<Channel*>	_channels;
		pollfd*					_clientsFd;
		CommandsUse*			_commands;
		std::string				_startTime;

		void	_createClientFds(void);
		void	_acceptConnection(void);
		void	_waitForConnections(void);
		void	_recvMessage(Client*);
		void	_parsMessage(std::string, Client*);
		void	_clientMessage(Client*);
		void	_setNonBlocking(int);

		Server();
		Server(Server const&);
		Server&	operator=(Server const&);

	public:
		Server(int, std::string const& password);
		~Server();

		void		IRC();
		ssize_t		send(std::string, int) 											const;
		void		addClient(int const, std::string const, int const);
		int			deleteClient(int);
		void		broadcast(std::string const&) 									const;
		void		broadcast(std::string const&, int) 								const;
		void		broadcastChannel(std::string const&, int, Channel const*)		const;
		void		broadcastChannel(std::string const&, Channel const*)			const;
		Channel*	createChannel(std::string const&, std::string const&, Client*);

		//setters:
		void	setSocketFd(int cp)							{_socketFd = cp;};
		void	setPort(int cp)								{_port = cp;};
		void	setPassword(std::string cp)					{_password = cp;};
		void	setServerName(std::string cp)				{_serverName = cp;};
		void	setClientsVector(std::vector<Client*> cp)	{_clientsReady = cp;};
		void	setClientsFd(pollfd* cp)					{_clientsFd = cp;};
		void	setCommands(CommandsUse* cp)				{_commands = cp;};

		//getters:
		std::string					getStartTime()					const	{return (_startTime);};
		int							getSocketFd()					const	{return (_socketFd);};
		int							getPort()						const	{return (_port);};
		std::string					getPassword()					const	{return (_password);};
		std::string					getServerName() 				const	{return (_serverName);};
		std::vector<Client*>		getClientsVector()				const	{return (_clientsReady);};
		std::vector<Channel *>		getChannels()					const	{return (_channels); };
		CommandsUse*				getCommands()					const	{return (_commands);};
		Channel*					getChannel(std::string const&);
		Client*						getClient(std::string const&);
		Client*						getClientsFd(int);
		std::vector<std::string>	getNicknames();
};