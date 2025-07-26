/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:54 by siuol             #+#    #+#             */
/*   Updated: 2025/07/26 15:16:13 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::handlerJoin(Client* client, std::string& channelName, std::string& pass)
{
    if (!this->isServerClient(client))
    {
        LOG_WARNING("[SERVER] : You are not in server");
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
    if (!this->isServerClient(client))
    {
        LOG_WARNING("[SERVER] : You are not in the server");
        std::cout << std::endl;
        return;
    }
    if (target[0] == '#')
    {
        std::string channelName = target.substr(1);
        if (!this->hasServerChannel(channelName))
        {
            LOG_WARNING("[SERVER] : Channel is not in the server");
            std::cout << std::endl;
            return; 
        }
        if (!this->_channelList[channelName]->isMember(client))
        {
            LOG_WARNING("[CHANNEL] : User is not in the channel");
            std::cout << std::endl;
            return; 
        }
        else
            //send msg to channel
    }
    else
    {
        if (!this->hasServerClient(target))
        {
            LOG_WARNING("[SERVER] : Receiver is not in the server");
            std::cout << std::endl;
            return; 
        }
        else
            //send msg to client   
    }
}

void    Server::handlerPart(Client* client, std::string& channelName, std::string& msg)
{
    if (!this->isServerClient(client))
    {
        LOG_WARNING("[SERVER] : You are not in the server");
        std::cout << std::endl;
        return;
    }
    if (!this->hasServerChannel(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in the server");
        std::cout << std::endl;
        return;
    }
    if (!this->_channelList[channelName]->isMember(client))
    {
        LOG_WARNING("[CHANNEL] : User is not in the channel");
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