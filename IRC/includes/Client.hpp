/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:50:22 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/23 11:32:09 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IRC.hpp"

//----------------------------------------------------------------------------||

typedef typename std::vector<Channel *>::iterator ChanVecIt;

//----------------------------------------------------------------------------||

class Channel;
class Server;

class Client{
	private:
		// * Utiles
		int						_socket;
		int						_port;
		std::string				_ip;
		bool					_passwordOk;

		// * Infos Serv
		Server *				_serv;
		std::vector<Channel *>	_usrChan;

		// * Infos Client
		std::string				_nickname;
		std::string				_username;
		std::string				_password;

	public:
		Client(int socket, Server *, std::string const & pseudo);
		Client(Server *, int const socket, std::string const ip, int const port);
		~Client();

		// * Fonctions
		bool	isConnected() const;
		void	linkSetMsg() const;

		void	sendMsg(const std::string & msg) const;
		void	joinChan(Channel *);
		void	leaveChan(Channel *, bool kicked, std::string const& reason);

		// * Getters
		int const						getClientSocket() const	{return _socket; };
		std::vector<Channel *> const	getUsrChan() const	{return _usrChan; };
		bool const						isPasswordOK() const	{return _passwordOk; };

		std::string const &				getNickname() const	{return _nickname; };
		std::string const &				getPassword() const	{return _password; };
		std::string const & 			getUsername() const	{return _username; };

		// * Setters
		void		setNickname(std::string const & ps)		{_nickname = ps; };
		void		setPassword(std::string const & pw)		{_password = pw; };
		void		setUsername(std::string const & us)		{_username = us; };
};