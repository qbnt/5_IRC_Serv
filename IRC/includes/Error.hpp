/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:40:04 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/29 10:20:30 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"

class Error{
	public:
	class Socket: public std::exception{
		public:
			virtual const char* what() const throw(){
				return ("Error: Socket().");
			}
	};

	class SocketOptions: public std::exception{
		public:
			virtual const char* what() const throw(){
				return ("Error: Cannot set Socket options.");
			}
	};

	class Bind: public std::exception{
		public:
			virtual const char* what() const throw(){
				return ("Error: Couldn't Bind.");
			}
	};

	class Listen: public std::exception{
		public:
			virtual const char* what() const throw(){
				return ("Error: Listen().");
			}
	};
};