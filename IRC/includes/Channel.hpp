/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:38:49 by qbanet            #+#    #+#             */
/*   Updated: 2024/05/01 17:26:25 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"

typedef typename std::vector<Client *>::iterator ChanIter;

class Channel {
	private:
		// * Infos Channel
		std::string		_name;
		std::string		_topic;
		std::string		_password;
		unsigned int	_maxUsr;

		// * Pointeur serveur
		Server *		_serv;

		// * Clients du channel
		Client *				_admin;
		std::vector<Client *>	_clients;
		std::vector<Client *>	_op;

	public:
		Channel(std::string const &name, std::string const &topic, std::string const &password, Client *admin, Server *serv);
		~Channel();

		// * Fonctions
		void							addUser(Client *);
		void							removeUser(Client *, std::string const& reason);
		void							removeOp(Client const *);
		void							diff(const std::string &);

		bool							isInChan(Client const *);
		bool							isOp(Client const *);
		unsigned int					getNbrUsr();
		std::vector<std::string>		getAllNickname();

		// * Getteurs
		std::string const &			getName() const		{return _name; };
		std::string const &			getTopic() const	{return _topic; };
		std::string const &			getPassword() const	{return _password; };
		unsigned int const &		getMaxUsr() const	{return _maxUsr; };

		Server const *				getServ() const		{return _serv; };
		Client const *				getAdmin() const	{return _admin; };
		std::vector<Client *> const	getClients() const	{return _clients; };
		std::vector<Client *> const	getOp()	const		{return _op; };
		Client const *				getClient(std::string const &);

		// * Setteurs
		void	setName(std::string const &name)		{_name = name; };
		void	setTopic(std::string const &topic)		{_topic = topic; };
		void	setPassword(std::string const &pw)		{_password = pw; };
		void	setMaxUsr(unsigned int const &nb)		{_maxUsr = nb; };

		void	setAdmin(Client * cl)					{_admin = cl; };
		void	setNewOp(Client * cl)					{_op.push_back(cl); };
};