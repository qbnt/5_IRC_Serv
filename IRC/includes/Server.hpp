/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:46:32 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/16 09:48:03 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"

class Server{
	public:
		Server();
		Server(Server const&);
		~Server();
		Server&	operator=(Server const&);
};