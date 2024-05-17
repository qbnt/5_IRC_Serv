/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:49:50 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/17 18:19:06 by qbanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

std::string ft_inet_ntop6(const void *a0)
{
	const unsigned char *a = (const unsigned char *)a0;
	int i, j, max, best;
	char buf[INET6_ADDRSTRLEN];

	if (memcmp(a, "\0\0\0\0\0\0\0\0\0\0\377\377", 12))
		snprintf(buf, sizeof buf,
			"%x:%x:%x:%x:%x:%x:%x:%x",
			256*a[0]+a[1],256*a[2]+a[3],
			256*a[4]+a[5],256*a[6]+a[7],
			256*a[8]+a[9],256*a[10]+a[11],
			256*a[12]+a[13],256*a[14]+a[15]);
	else
		snprintf(buf, sizeof buf,
			"%x:%x:%x:%x:%x:%x:%d.%d.%d.%d",
			256*a[0]+a[1],256*a[2]+a[3],
			256*a[4]+a[5],256*a[6]+a[7],
			256*a[8]+a[9],256*a[10]+a[11],
			a[12],a[13],a[14],a[15]);
	/* Replace longest /(^0|:)[:0]{2,}/ with "::" */
	for (i=best=0, max=2; buf[i]; i++) {
		if (i && buf[i] != ':') continue;
		j = strspn(buf+i, ":0");
		if (j>max) best=i, max=j;
	}
	if (max>3) {
		buf[best] = buf[best+1] = ':';
		memmove(buf+best+2, buf+best+max, i-best-max+1);
	}
	return (buf);
}


std::string	timeString(){
	time_t	rawtime;
	struct	tm*timeinfo;
	char	buff[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buff, sizeof(buff), "%c", timeinfo);
	return (buff);
}

std::vector<std::string> ft_split(const std::string& str, char c) {
    std::vector<std::string> cmd;
    size_t start = 0;
    size_t end = 0;

    while (end < str.size()) {
        while (end < str.size() && str[end] != c) {
            end++;
        }
        cmd.push_back(str.substr(start, end - start));
        end++;
        start = end;
    }

    if (start < str.size() || (start == str.size() && !str.empty() && str[str.size() - 1] == c)) {
        cmd.push_back("");
    }

    return cmd;
}

int	allDigits(char *ag){
	for (long unsigned int i = 0; i < strlen(ag); i++)
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
	Server(atoi(ag[1]), ag[2]);
	return 0;
}