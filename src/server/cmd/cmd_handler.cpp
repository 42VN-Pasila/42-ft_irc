/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:54 by siuol             #+#    #+#             */
/*   Updated: 2025/07/28 00:32:29 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::handlerJoin(Client& client, std::string& channelName, std::string& pass)
{
    if (!this->hasServerChannel(channelName))
    {
        Channel newChannel = Channel(channelName);
        this->_channelList.insert({channelName, newChannel});
        newChannel.addUser(client);
        newChannel.setOperator(client);
    }
    else if (!this->passwordRequired(this->_channelList[channelName], pass))
        return ;
    else
        this->_channelList[channelName].addUser(client);
}

void    Server::handlerPrivmsg(Client& client, std::string& target, std::string& msg)
{
    if (target[0] == '#')
    {
        std::string channelName = target.substr(1);
        if (!this->hasServerChannel(channelName))
        {
            LOG_WARNING("[SERVER] : Channel is not in the server");
            std::cout << std::endl;
            return; 
        }
        if (!this->_channelList[channelName].isMember(client))
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

void    Server::handlerPart(Client& client, std::string& channelName, std::string& msg)
{
    if (!this->hasServerChannel(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in the server");
        std::cout << std::endl;
        return;
    }
    if (!this->_channelList[channelName].isMember(client))
    {
        LOG_WARNING("[CHANNEL] : User is not in the channel");
        std::cout << std::endl;
        return; 
    }
    else
    {
        std::string channel = "#" + channelName;
        this->_channelList[channelName].removeUser(client);
        if (!msg.empty())
            handlerPrivmsg(client, channel, msg);
    }
}

void    Server::handlerKick(Client& client, std::string& channelName, std::string& targetUser)
{
    if (!this->hasServerChannel(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in the server");
        std::cout << std::endl;
        return;
    }
    if (!this->_channelList[channelName].isMember(client))
    {
        LOG_WARNING("[CHANNEL] : User is not in the channel");
        std::cout << std::endl;
        return; 
    }
    if (!this->_channelList[channelName].isOperator(client))
    {
        LOG_WARNING("[CHANNEL] : User is not the operator of the channel");
        std::cout << std::endl;
        return; 
    }
    if (!this->hasServerClient(targetUser))
    {
        LOG_WARNING("[SERVER] : Receiver is not in the server");
        std::cout << std::endl;
        return; 
    }
    if (!this->_channelList[channelName].isMember(this->_clientList[targetUser]))
    {
        LOG_WARNING("[CHANNEL] : Receiver is not in the channel");
        std::cout << std::endl;
        return; 
    }
    this->_channelList[channelName].kickUser(this->_clientList[targetUser]);
}