/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:46:32 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/27 19:39:59 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"

class Client;
class Server: public Error{
	private:
	
		int						_port;
		std::string				_password;
		std::string 			_serverName;
		int						_socketFd;
		std::vector<Client *>	_clientsReady;
		pollfd*					_clientsFd;
		CommandsUse				_commands;

		void	_createClientFds(void);
		void	_acceptConnection(void);
		void	_waitForConnections(void);
		void	_clientMessage(Client*);
		void	_parsMessage(std::string, Client*);

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
		int		getSocketFd() const	{ return (_socketFd);};
};