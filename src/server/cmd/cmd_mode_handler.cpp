/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode_handler.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:03:37 by caonguye          #+#    #+#             */
/*   Updated: 2025/07/29 00:39:33 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::handlerModeI(Client* client, std::string& channelName, bool mode)
{
    if (!this->hasServerChannel(channelName))
        Notifyer::notifyError(client, 403);
    if (!this->_channelList[channelName]->isMember(client))
        Notifyer::notifyError(client, 442);
    if (!this->_channelList[channelName]->isOperator(client))
        Notifyer::notifyError(client, 482);
    this->_channelList[channelName]->setInviteStatus(mode);
}

void    Server::handlerModeT(Client* client, std::string& channelName, bool mode)
{
    if (!this->hasServerChannel(channelName))
        Notifyer::notifyError(client, 403);
    
}

void    Server::handlerModeK(Client* client, std::string& channelName, const std::string& pass, bool mode)
{
    if (!this->hasServerChannel(channelName))
        Notifyer::notifyError(client, 403);
    if (!this->_channelList[channelName]->isMember(client))
        Notifyer::notifyError(client, 442);
    if (!this->_channelList[channelName]->isOperator(client))
        Notifyer::notifyError(client, 482);
    if (mode == on)
        this->_channelList[channelName]->setPassword(pass);
    else
        this->_channelList[channelName]->unsetPassword();
}

void    Server::handlerModeO(Client* client, std::string& channelName, std::string& nickName, bool mode)
{
    if (!this->hasServerChannel(channelName))
        Notifyer::notifyError(client, 403);
    
}

void    Server::handlerModeL(Client* client, std::string& channelName, const unsigned int limit, bool mode)
{
    if (!this->hasServerChannel(channelName))
        Notifyer::notifyError(client, 403);
    if (!this->_channelList[channelName]->isMember(client))
        Notifyer::notifyError(client, 442);
    if (!this->_channelList[channelName]->isOperator(client))
        Notifyer::notifyError(client, 482);
    if (mode == on)
        this->_channelList[channelName]->setLimit(limit);
    else
        this->_channelList[channelName]->unsetLimit();
}
