/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:46:32 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/17 09:32:30 by mescobar         ###   ########.fr       */
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

		Server();
		Server(Server const&);
		Server&	operator=(Server const&);

	public:
		Server(int, std::string const& password);
		~Server();

		void	IRC();
		void	waitForConnections();
		int		getSocketFd() const	{ return (_socketFd);};
};