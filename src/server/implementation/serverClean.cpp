/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverClean.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:18:31 by siuol             #+#    #+#             */
/*   Updated: 2025/08/15 20:36:57 by htran-th         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void Channel::cleanUp()
{
    this->_operator = nullptr;
    this->_members.clear();
    this->_invitation.clear(); 
}

Server::~Server()
{
    
    for (auto& pair : _channelList)
    {
        Channel* channel = pair.second;
        
        channel->cleanUp();
        delete channel;
    }
    
    // for (auto& pair : _clientList)
    // {
    //     Client* client = pair.second;
        
    //     delete client;
    // }

    // closeAllFds();
    
    this->_channelList.clear();
    this->_clientList.clear();
    // this->_socketList.clear();

    for (size_t i = 1; i < _poll_fds.size(); ++i) {
        int fd = _poll_fds[i].fd;
        close(fd);
        if (std::map<int,Client*>::iterator it = _socketList.find(fd);
            it != _socketList.end()) {
            delete it->second;
            _socketList.erase(it);
        }
    }
    _poll_fds.clear();
    if (_server_fd >= 0) {
        close(_server_fd); _server_fd = -1;
    }

    std::cout << "Shutting down server!" << std::endl;
}