/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:46:32 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/24 12:02:00 by mescobar         ###   ########.fr       */
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
		Commands				_commands;

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
		void	addClient(int const, std::string const, int const);
		void	deleteClient(int);
		int		getSocketFd() const	{ return (_socketFd);};
};