/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:40:04 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/16 13:14:24 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"

class Socket: public std::exception{
	public:
		virtual const char* what() const throw(){
			return ("Socket() error, -1 returned.");
		}
};

class Listen: public std::exception{
	public:
		virtual const char* what() const throw(){
			return ("Listen() error, -1 returned.");
		}
};