/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_init.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:56:30 by htran-th          #+#    #+#             */
/*   Updated: 2025/08/06 02:01:32 by htran-th         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void Server::closeAllFds() { // Temporarily here, move to a proper folder/file later
    for (pollfd pfd : _poll_fds) {
        if (pfd.fd >= 0) {
            close(pfd.fd);
        }
    }
}

/*
Function to set non-blocking mode to the input file descriptor.
- retrieves the current flags
- sets the current flags and add O_NONBLOCK
- throw an std::runtime_error if failed
*/
void setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0 || fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) {
        throw std::runtime_error("fcntl: failed to set non-blocking mode!");
    }
}

bool launchServer(char* password, int *iport)
{
    Server server(*iport, password);
    
    try {
        server.initSocket();
        server.bindAndListen();
        server.pollAndAccept();
        // TODO: read the actual input
    } catch(const std::exception& e) {
        throw ;
        return false;
    } 
    return true;
}