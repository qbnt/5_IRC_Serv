/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:38:49 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/03 12:23:49 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"

typedef typename std::vector<Client *>::iterator ChanIter;

class Channel {
	private:
		// * Infos Channel
		std::string		_name;
		unsigned int	_maxUsr;
		bool			_inviteMode;
		std::string		_password;

		// * Pointeur serveur
		Server *		_serv;

		// * Clients du channel
		Client *				_admin;
		std::vector<Client *>	_clients;
		std::vector<Client *>	_op;

	public:
		Channel(std::string const &name, std::string const &password, Client *admin, Server *serv);
		~Channel();

		// * Fonctions
		void							diff(const std::string &);
		void							addUser(Client *);
		void							removeUser(Client *, std::string reason);
		void							addOp(Client * cl);
		void							removeOp(Client *, Client *target, std::string reason);
		void							kick(Client *, Client * target, std::string reason);
		void							invit(Client *, Client * target);

		bool							isInChan(Client const *);
		bool							isOp(Client const *);
		unsigned int					getNbrUsr();
		std::vector<std::string>		getAllNickname();
		unsigned long 					clientIndex(std::vector<Client *> clients, Client *client);

		// * Getteurs
		std::string const &			getName() const		{return _name; };
		unsigned int const &		getMaxUsr() const	{return _maxUsr; };
		bool const &				getInvMode() const	{return _inviteMode; };
		std::string const &			getPassword() const	{return _password; };

		Server const *				getServ() const		{return _serv; };
		Client const *				getAdmin() const	{return _admin; };
		std::vector<Client *> const	getClients() const	{return _clients; };
		std::vector<Client *> const	getOp()	const		{return _op; };
		Client const *				getClient(std::string const &);

		// * Setteurs
		void	setName(std::string const &name)		{_name = name; };
		void	setMaxUsr(unsigned int const &nb)		{_maxUsr = nb; };
		void	setInvMode(bool oui)					{_inviteMode = oui; };
		void	setPassword(std::string const &pw)		{_password = pw; };

		void	setAdmin(Client * cl)					{_admin = cl; };
};