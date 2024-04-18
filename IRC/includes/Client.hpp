/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:50:22 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/18 11:15:28 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IRC.hpp"

//----------------------------------------------------------------------------||

typedef typename std::vector<Channel *>::iterator ChanVecIt;

//----------------------------------------------------------------------------||

class Client{
	private:
		// * Utiles
		int						_socket;
		int						_port;
		std::string				_ip;
		bool					_isConnected;

		// * Infos Serv
		Server *				_serv;
		std::vector<Channel *>	_usrChan;

		// * Infos Client
		std::string				_pseudo;
		std::string				_password;
		std::string				_username;
		std::string				_fullname;

		// Client();
		// Client(Client const&);
		// Client& operator=(Client const&);

	public:
		Client(int socket, Server *, std::string const & pseudo);
		Client(int const socket, std::string const ip, int const port);
		~Client();

		// * Fonctions
		void	linkSetMsg() const;
		void	joinChan(Channel *);
		void	leaveChan(Channel *, bool kicked, std::string const& reason);

		// * Getters
		int const						getClientSocket() const	{return _socket; };
		std::vector<Channel *> const	getUsrChan() const	{return _usrChan; };
		bool const						isConnected() const	{return _isConnected; };

		std::string const &				getPseudo() const	{return _pseudo; };
		std::string const &				getPassword() const	{return _password; };
		std::string const & 			getUsername() const	{return _username; };
		std::string const &				getFullname() const	{return _fullname; };

		// * Setters
		void		setPseudo(std::string const & ps)		{_pseudo = ps; };
		void		setPassword(std::string const & pw)		{_password = pw; };
		void		setUsername(std::string const & us)		{_username = us; };
		void		setFullname(std::string const & fu)		{_fullname = fu; };
};