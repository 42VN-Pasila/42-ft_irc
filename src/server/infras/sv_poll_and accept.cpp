/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_poll_and accept.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 21:55:53 by htran-th          #+#    #+#             */
/*   Updated: 2025/08/06 02:32:37 by htran-th         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void Server::pollAndAccept() {
    pollfd s_pfd = {.fd = _server_fd, .events = POLLIN, .revents = 0};
    _poll_fds.push_back(s_pfd);

    while (true) {
        int ret = poll(_poll_fds.data(), _poll_fds.size(), -1);
        if (ret < 0) {
            throw std::runtime_error("Server: poll failed!");
        }
        if (_poll_fds[0].revents & POLLIN) {
            struct sockaddr_in client_addr;
            socklen_t addr_len = sizeof(client_addr);
        
            int client_fd = accept(_server_fd, (struct sockaddr *)&client_addr, &addr_len);
            if (client_fd < 0) {
                throw std::runtime_error("Server: failed to accept a client connection!");
            }
            setNonBlocking(client_fd);
        
            pollfd c_pfd = {.fd = client_fd, .events = POLLIN, .revents = 0};
            _poll_fds.push_back(c_pfd);
            
            std::cout << "New client connected: fd = " << client_fd << std::endl; // TODO: delete?
            
            // TODO: Record new client(s) to client list
            /*
            Issue: Before registering (provide valid NICK & USER, a client is already connected).
            Therefore we need to add it to the client list with the only information we have: int client_fd.
            So Server needs a std::map<int, Client*>; (delete in destructor)
            */
        //     Client *new_client = new Client(client_fd);
        //     _cl_nonverify[client_fd] = new_client;
        }
    }
}