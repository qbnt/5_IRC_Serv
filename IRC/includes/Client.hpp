/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:50:22 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/03 11:55:08 by mescobar         ###   ########.fr       */
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
		std::string				_hostname;
		bool					_passwordOk;

		// * Infos Serv
		Server *				_serv;
		std::vector<Channel *>	_usrChan;

		// * Infos Client
		std::string				_nickname;
		std::string				_username;
		std::string				_realname;

	public:
		Client(Server *, int const socket, std::string const &hn, int const port);
		~Client();

		// * Fonctions
		bool const			isOk() const;
		void				send(const std::string &) const;
		void				sendMsg(const std::string & msg) const;
		std::string const	getPref() const;
		void				linkSetMsg() const;

		void	joinChan(Channel *);
		void	leaveChan(Channel *, bool kicked, std::string const& reason);

		// * Getters
		int const						getClientSocket() const	{return _socket; };
		std::vector<Channel *> const	getUsrChan() const		{return _usrChan; };
		std::string const				getHostname() const		{return _hostname; };
		bool const						isPasswordOK() const	{return _passwordOk; };

		std::string const &				getNickname() const	{return _nickname; };
		std::string const & 			getUsername() const	{return _username; };
		std::string const &				getRealname() const	{return _realname; };

		// * Setters
		void		setNickname(std::string const & ps)		{_nickname = ps; };
		void		setUsername(std::string const & us)		{_username = us; };
		void		setRealname(std::string const & pw)		{_realname = pw; };
};