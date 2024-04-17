/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:50:22 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/17 09:06:13 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"

class Client{
	private:
		int	fd;
	public:
		Client();
		Client(Client const&);
		~Client();
		Client& operator=(Client const&);
		int		getClientFd() const;
};