/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:49:50 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/17 08:09:30 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

int	allDigits(char *ag){
	for (int i = 0; i < strlen(ag); i++)
		if (!isdigit(ag[i]))
			return (0);
	return (1);
}

int	main(int ac, char** ag){
	if (ac != 3){
		std::cout << "Invalid number of arguments, try: ./ircserv <port> <password>" << std::endl;
		return (0);
	}
	else if (!allDigits(ag[1])){
		std::cout << "Invalid <port>, use only digits" << std::endl;
		return (0);
	}
	Server serv = Server(atoi(ag[1]), ag[2]);
	return 0;
}