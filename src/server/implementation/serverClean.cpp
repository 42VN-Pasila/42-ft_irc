/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverClean.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:18:31 by siuol             #+#    #+#             */
/*   Updated: 2025/09/14 11:08:47 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void Channel::cleanUp()
{
    this->_operators.clear();
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

void    Server::removeChannel(Channel* channel)
{
    if (channel->isEmpty())
    {
        std::string channelName = channel->getChannelName();
        this->_channelList.erase(channelName);
        channel->cleanUp();
        delete channel;
    }
}