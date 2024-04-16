/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:49:14 by mescobar          #+#    #+#             */
/*   Updated: 2024/04/16 09:52:43 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iostream"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "netdb.h"
#include "csignal"
#include "signal.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "poll.h"
#include "Server.hpp"
#include "Client.hpp"

typedef struct	s_data{
}				t_data;