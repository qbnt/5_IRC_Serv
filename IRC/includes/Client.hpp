/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:50:22 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/16 09:51:07 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"

class Client{
	public:
		Client();
		Client(Client const&);
		~Client();
		Client& operator=(Client const&);
};