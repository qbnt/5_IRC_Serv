/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbanet <qbanet@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:49:14 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/17 14:41:37 by qbanet           ###   ########.fr       */
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

# define SOCKET_ERROR -1
# define DEFAULT_PORT 6667
# define DEFAULT_SERVER_NAME "irc.42.fr"
