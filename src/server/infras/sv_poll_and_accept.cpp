/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_poll_and_accept.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:00:42 by htran-th          #+#    #+#             */
/*   Updated: 2025/08/07 19:47:47 by htran-th         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void Server::removeClient(int client_fd, int index) {
    close(client_fd);
    _poll_fds.erase(_poll_fds.begin() + index);
    delete _socketList[client_fd];
    _socketList.erase(client_fd);
}

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
            
            std::cout << "New client connected: fd = " << client_fd << std::endl;

            
            Client *new_client = new Client(client_fd); //TODO: error check
            _socketList[client_fd] = new_client;
        }
        for (size_t i = 1; i < _poll_fds.size(); ++i) {
            if (_poll_fds[i].revents & POLLIN) {
                char buffer[1000];
                int client_fd = _poll_fds[i].fd;
                ssize_t bytesRead = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
                if (bytesRead <= 0) { //TODO: check errno
                   std::cerr << RED << "Client disconnected: fd = " << client_fd << RESET << std::endl;
                   removeClient(client_fd, i);
                   --i; // because the rest of the array shifted one place to the left
                   continue ; // checks the rest of the clients
                }
                buffer[bytesRead] = '\0';
                std::cout << "Message from client(fd " << client_fd << "): " << buffer << std::endl;
            }
        }
    }
}