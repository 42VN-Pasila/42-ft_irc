/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode_handler.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:03:37 by caonguye          #+#    #+#             */
/*   Updated: 2025/07/27 01:12:14 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::handlerModeI(Client* client, std::string& channelName, bool mode)
{
    if (!this->hasServerChannel(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in the server");
        std::cout << std::endl;
        return ;
    }
    if (!this->_channelList[channelName]->isMember(client))
    {
        LOG_WARNING("[CHANNEL] : You are not the member of this channel");
        std::cout << std::endl;
        return ;
    }
    if (!this->_channelList[channelName]->isOperator(client))
    {
        LOG_WARNING("[CHANNEL] : You are not the operator");
        std::cout << std::endl;
        return ;
    }
    this->_channelList[channelName]->setInviteStatus(mode);
}

void    Server::handlerModeT(Client* client, std::string& channelName, bool mode)
{
    if (!this->hasServerChannel(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in the server");
        std::cout << std::endl;
        return ;
    }
    
}

void    Server::handlerModeK(Client* client, std::string& channelName, const std::string& pass, bool mode)
{
    if (!this->hasServerChannel(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in the server");
        std::cout << std::endl;
        return ;
    }
    if (!this->_channelList[channelName]->isMember(client))
    {
        LOG_WARNING("[CHANNEL] : You are not the member of this channel");
        std::cout << std::endl;
        return ;
    }
    if (!this->_channelList[channelName]->isOperator(client))
    {
        LOG_WARNING("[CHANNEL] : You are not the operator");
        std::cout << std::endl;
        return ;
    }
    if (mode == on)
        this->_channelList[channelName]->setPassword(pass);
    else
        this->_channelList[channelName]->unsetPassword();
}

void    Server::handlerModeO(Client* client, std::string& channelName, std::string& nickName, bool mode)
{
    if (!this->hasServerChannel(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in the server");
        std::cout << std::endl;
        return ;
    }
    
}

void    Server::handlerModeL(Client* client, std::string& channelName, const unsigned int limit, bool mode)
{
    if (!this->hasServerChannel(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in the server");
        std::cout << std::endl;
        return ;
    }
    if (!this->_channelList[channelName]->isMember(client))
    {
        LOG_WARNING("[CHANNEL] : You are not the member of this channel");
        std::cout << std::endl;
        return ;
    }
    if (!this->_channelList[channelName]->isOperator(client))
    {
        LOG_WARNING("[CHANNEL] : You are not the operator");
        std::cout << std::endl;
        return ;
    }
    if (mode == on)
        this->_channelList[channelName]->setLimit(limit);
    else
        this->_channelList[channelName]->unsetLimit();
}
