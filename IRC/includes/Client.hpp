/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:50:22 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/18 14:02:18 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IRC.hpp"

class Channel;
class Server;

//----------------------------------------------------------------------------||

typedef typename std::vector<Channel *>::iterator ChanVecIt;

//----------------------------------------------------------------------------||


class Client{
	private:
		// * Utiles
		struct pollfd*			_clientFd;
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
		std::string				_message;

	public:
		Client(Server *, int const socket, std::string const &hn, int const port);
		~Client();

		// * Fonctions
		bool				isOk() const;
		void				send(const std::string &) const;
		void				sendMsg(const std::string & msg) const;
		std::string const	getPref() const;
		void				linkSetMsg() const;

		void	joinChan(Channel *);
		void	leaveChan(Channel *, bool kicked, std::string const& reason);

		// * Getters
		int								getClientSocket() const	{return _socket; };
		struct pollfd*					getClientpollfd() const	{return _clientFd; };
		std::vector<Channel *> const	getUsrChan() const		{return _usrChan; };
		std::string const				getHostname() const		{return _hostname; };
		bool							isPasswordOK() const	{return _passwordOk; };

		std::string const &				getNickname() const	{return _nickname; };
		std::string const & 			getUsername() const	{return _username; };
		std::string const &				getRealname() const	{return _realname; };
		std::string const &				getMessage()  const	{return _message;};

		// * Setters
		void		setMessage(std::string const & ps)		{_message = ps;};
		void		setNickname(std::string const & ps)		{_nickname = ps; };
		void		setUsername(std::string const & us)		{_username = us; };
		void		setRealname(std::string const & pw)		{_realname = pw; };
		void		setPasswordOk(bool const& pw)			{_passwordOk = pw; };
		void		setClientPollFd(struct pollfd *oui)		{_clientFd = oui; };
};