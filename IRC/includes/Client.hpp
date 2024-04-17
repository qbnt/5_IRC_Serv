/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:50:22 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/17 14:41:12 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"

class Client{
	private:
		int						_fd;
		std::vector<Channel *>	_usrChan;

		std::string				_pseudo;
		std::string				_username;
		std::string				_fullname;

		Client();
		Client(Client const&);
		Client& operator=(Client const&);

	public:
		Client(int fd, std::string const & pseudo);
		~Client();

		int						getClientFd() const	{return _fd; };
		std::vector<Channel *>	getUsrChan() const	{return _usrChan; };

		std::string const &		getPseudo() const	{return _pseudo; };
		std::string const & 	getUsername() const	{return _username; };
		std::string const &		getFullname() const	{return _fullname; };

		void					setPseudo(std::string const & ps)		{_pseudo = ps; };
		void					setUsername(std::string const & us)	{_username = us; };
		void					setFullname(std::string const & fu)	{_fullname = fu; };
};