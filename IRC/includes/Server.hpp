/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:46:32 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/18 09:59:21 by mescobar         ###   ########.fr       */
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

		void	_createClientFds(void);
		void	_acceptConnection(void);
		void	_waitForConnections(void);

		Server();
		Server(Server const&);
		Server&	operator=(Server const&);

	public:
		Server(int, std::string const& password);
		~Server();

		void	IRC();
		int		getSocketFd() const	{ return (_socketFd);};
};