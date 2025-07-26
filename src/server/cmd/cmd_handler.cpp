/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:54 by siuol             #+#    #+#             */
/*   Updated: 2025/07/26 05:30:15 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::handlerJoin(Client* client, std::string& channelName, std::string& pass)
{
    if (!this->isServerClient(client))
    {
        LOG_WARNING("[SERVER] : Client is not in server");
        std::cout << std::endl;
        return;
    }
    if (!this->hasServerChannel(channelName))
    {
        Channel* newChannel = new Channel(channelName);
        this->_channelList.insert({channelName, newChannel});
        newChannel->addUser(client);
        newChannel->setOperator(client);
    }
    else if (!this->passwordRequired(this->_channelList[channelName], pass))
        return ;
    else
        this->_channelList[channelName]->addUser(client);
}

void    Server::handlerPrivmsg(Client* client, std::string& target, std::string& msg)
{
    
}

void    Server::handlerPart(Client* client, std::string& channelName, std::string& msg)
{
    if (!this->isServerClient(client))
    {
        LOG_WARNING("[SERVER] : Client is not in the server");
        std::cout << std::endl;
        return;
    }
    if (this->hasServerChannel(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in the server");
        std::cout << std::endl;
        return;
    }
    else
    {
        this->_channelList[channelName]->removeUser(client);
        if (!msg.empty())
            handlerPrivmsg(client, channelName, msg);
    }
}