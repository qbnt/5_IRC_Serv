/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:49:14 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/16 13:25:16 by mescobar         ###   ########.fr       */
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
# include "netdb.h"
# include "csignal"
# include "signal.h"
# include "sys/stat.h"
# include "fcntl.h"
# include "poll.h"
# include "ctime"
# include "vector"
# include "map"

# include "Server.hpp"
# include "Client.hpp"
# include "Error.hpp"

# define SOCKET_ERROR -1
# define DEFAULT_PORT 6667
# define DEFAULT_SERVER_NAME "irc.42.fr"