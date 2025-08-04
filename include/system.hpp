/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:30:42 by siuol             #+#    #+#             */
/*   Updated: 2025/08/04 21:34:37 by htran-th         ###   ########.fr       */
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
#include <charconv>
#include <sstream>
#include <functional>
#include "client.hpp"
#include "channel.hpp"
#include "server.hpp"
#include "notifyer.hpp"
#include "parser.hpp"

class Notifyer;
class Client;
class Channel;
class Server;

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
