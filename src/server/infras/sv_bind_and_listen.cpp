/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_bind_and_listen.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:14:41 by htran-th          #+#    #+#             */
/*   Updated: 2025/08/06 20:54:56 by htran-th         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void Server::bindAndListen() {
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET; // Set the address family to IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address on this machine
    server_addr.sin_port = htons(_port); // Convert the port to network byte order (LE to BE)

    int opt = 1;
    if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        throw std::runtime_error("Server: setsockopt failed!");
    }
    // Bind the socket to the address and port
    if (bind(_server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        throw std::runtime_error("Server: binding failed!");
    }

    // Listen for incoming connections
    if (listen(_server_fd, LIMIT_MEMBER) < 0) { // ulimit -n 1024 fds max, for one channel maybe less?
        throw std::runtime_error("Server: listen failed!");
    }

    std::cout << "Server listening on port " << _port << std::endl;
}