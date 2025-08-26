/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_poll_and_accept.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:00:42 by htran-th          #+#    #+#             */
/*   Updated: 2025/08/26 16:12:39 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

volatile sig_atomic_t g_running = 1;

static signal_cont_handler(int signal, Client* client)
{
    
}

void signal_handler(int signal) {
    g_running = 0;
    if (signal == SIGCONT)
        signal_cont_handler();
    std::cout << "\n" << (signal == SIGINT ? "SIGINT" : "SIGQUIT") << " caught!" << std::endl;
}

int Server::getIndex(int fd) const {
    for (int i = 0; i < this->_poll_fds.size(); i++) {
        if (fd == this->_poll_fds[i].fd) {
            return i;
        }
    }
    return -1;
}

void Server::removeClient(int client_fd, int index) 
{
    if (_socketList.find(client_fd) == _socketList.end()) {
        return; 
    }
    
    Client* client = this->_socketList[client_fd];
    
    this->_clientList.erase(client->getNickName());

    for (auto& pair : _channelList)
    {
        if (pair.second->isMember(client)) {
            pair.second->removeUser(client);
        }
    }
    
    close(client_fd);
    if (index >= 0 && index < static_cast<int>(_poll_fds.size())) {
        _poll_fds.erase(_poll_fds.begin() + index);
    }
 
    delete client;
    _socketList.erase(client_fd);
}

void Server::pollAndAccept() {
    int quitFlag  = 0;
    std::signal(SIGINT, signal_handler);
    std::signal(SIGQUIT, signal_handler);
    std::signal(SIGCONT, signal_handler);
    pollfd s_pfd = {.fd = _server_fd, .events = POLLIN, .revents = 0};
    _poll_fds.push_back(s_pfd);

    while (g_running) {
        int ret = poll(_poll_fds.data(), _poll_fds.size(), -1);
        if (ret < 0) {
            if (errno == EINTR) {
                continue; // g_running now changed -> break
            }
            throw std::runtime_error("Server: poll failed!");
        }
        if (_poll_fds[0].revents & POLLIN) {
            struct sockaddr_in client_addr;
            socklen_t addr_len = sizeof(client_addr);
        
            int client_fd = accept(_server_fd, (struct sockaddr *)&client_addr, &addr_len);
            if (client_fd < 0) {
                if (errno == EINTR)
                    continue;
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
                if (bytesRead <= 0) {
                    if (errno == EINTR)
                        continue;
                    std::cout << RED << "Client disconnected: fd = " << client_fd << RESET << std::endl;
                    removeClient(client_fd, i);
                    --i; // because the rest of the array shifted one place to the left
                    continue ; // checks the rest of the clients
                }
                buffer[bytesRead] = '\0';
                std::string message(buffer);
                if (!message.empty())
                { 
                    Client *client = _socketList[client_fd];
                    parseCommand(client, message, quitFlag);
                    std::cout << "Message from client(fd " << client_fd << "): " << buffer << std::endl; // Temporarily here - delete later
                    if (quitFlag)
                    {
                        --i;
                        quitFlag = 0;
                        std::cout << RED << "Client disconnected: fd = " << client_fd << RESET << std::endl;
                        continue;
                    }
                }
            }
        }
    }
}

