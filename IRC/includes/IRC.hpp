/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:49:14 by mescobar          #+#    #+#             */
/*   Updated: 2024/05/01 13:34:14 by qbanet           ###   ########.fr       */
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
# include "fcntl.h"
# include "poll.h"
# include "vector"
# include "map"

# include "Server.hpp"
# include "Channel.hpp"
# include "Client.hpp"
# include "Error.hpp"
# include "Command.hpp"
# include "CommandsUse.hpp"
# include "rpl.hpp"

# define BUFFER_SIZE			8192
# define SOCKET_ERROR			-1
# define DEFAULT_PORT			6667
# define DEFAULT_SERVER_NAME	"irc.42.fr"
# define VERSION				"0.42"
# define USERMODES				""
# define CHANNELMODES			"tikol"

std::vector<std::string> ft_split(std::string, char);
