/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:30:42 by siuol             #+#    #+#             */
/*   Updated: 2025/09/25 23:05:27 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <csignal>
#include <charconv>
#include <sstream>
#include <functional>
#include <unistd.h>
#include <string.h>

#include "client.hpp"
#include "channel.hpp"
#include "server.hpp"
#include "notifyer.hpp"
#include "parser.hpp"
#include "infras.hpp"

class Server;
class Notifyer;
class Client;
class Channel;

// Color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

// Logging macros
#define LOG_SUCCESS(msg) std::cout << GREEN << msg << RESET
#define LOG_ERROR(msg)   std::cerr << RED << msg << RESET
#define LOG_WARNING(msg) std::cout << YELLOW << msg << RESET
#define LOG_INFO(msg)    std::cout << BLUE << msg << RESET
#define LOG_DEBUG(msg)   std::cout << CYAN << msg << RESET

#define LIMIT_MEMBER 1000
#define on true
#define off false
#define MULTI_TARGET_FUNCTIONS 2
#define MODE_QTT    5

#define CMD_STANDARD    1000
#define MSG_SIZE        512
#define PASSWORD_SIZE   14             
