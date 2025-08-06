/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverClean.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:18:31 by siuol             #+#    #+#             */
/*   Updated: 2025/08/06 20:49:32 by htran-th         ###   ########.fr       */
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
        
        delete client;
    }

    closeAllFds();
    
    this->_channelList.clear();
    this->_clientList.clear();
    this->_socketList.clear();

    std::cout << "Shutting down server!" << std::endl;
}