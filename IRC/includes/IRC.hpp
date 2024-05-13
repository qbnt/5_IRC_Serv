/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:49:14 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/13 13:22:59 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "iostream"
# include "stdlib.h"
# include "string.h"
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include "netinet/in.h"
# include "netdb.h"
# include "csignal"
# include "signal.h"
# include "sys/stat.h"
# include "numeric"
# include "sstream"
# include "fcntl.h"
# include "poll.h"
# include "vector"
# include "map"
# include "sys/time.h"
# include "ctime"
# include "stdio.h"

# include "Channel.hpp"
# include "Client.hpp"
# include "Command.hpp"
# include "CommandsUse.hpp"
# include "Error.hpp"
# include "rpl.hpp"
# include "Server.hpp"

# define BUFFER_SIZE			8192
# define SOCKET_ERROR			-1
# define DEFAULT_PORT			6667
# define DEFAULT_SERVER_NAME	"irc.42.fr"
# define VERSION				"0.42"
# define USERMODES				""
# define CHANNELMODES			"tikol"
# define KICKDEFREASON			"Bha je sais pas lol"

std::vector<std::string>	ft_split(std::string, char);
std::string					timeString(void);
std::string 				ft_inet_ntop6(const void *a0);
