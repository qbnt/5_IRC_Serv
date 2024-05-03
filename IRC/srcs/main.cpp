/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:49:50 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/03 12:34:22 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

std::string	timeString(){
	time_t	rawtime;
	struct	tm*timeinfo;
	char	buff[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buff, sizeof(buff), "%c", timeinfo);
	return (buff);
}

std::vector<std::string>	ft_split(std::string str, char c){
	std::vector<std::string>	cmd;
	int j = 0;
	if (str.empty())
		cmd.push_back("");
	for (int i = 0; i < str.size(); i++){
		while (str[i] && str[i] != c)
			i++;
		cmd.push_back(str.substr(j, i));
		j += i;
	}
	return (cmd);
}

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