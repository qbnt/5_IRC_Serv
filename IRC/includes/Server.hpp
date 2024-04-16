/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:46:32 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/16 13:20:50 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"

class Server{
	private:
		int		_socketFd;
		int		_clientsReady;
		time_t	_time;
		pollfd*	_clientsFd;

	public:
		Server();
		Server(Server const&);
		~Server();
		Server&	operator=(Server const&);

		int		getSocketFd() const	{ return (_socketFd);};
};