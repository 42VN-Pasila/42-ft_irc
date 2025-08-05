/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverClean.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:18:31 by siuol             #+#    #+#             */
/*   Updated: 2025/08/06 02:47:56 by siuol            ###   ########.fr       */
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
    
    for (auto& pair : _clientList)
    {
        Client* client = pair.second;
        
        close(client->getSocket());
        delete client;
    }
    
    this->_channelList.clear();
    this->_clientList.clear();
    this->_socketList.clear();
}