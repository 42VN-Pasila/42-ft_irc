/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:54 by siuol             #+#    #+#             */
/*   Updated: 2025/07/29 02:09:13 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::handlerJoin(Client* client, std::string& channelName, std::string& pass)
{
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
    if (target[0] == '#')
    {
        std::string channelName = target.substr(1);
        if (!this->hasServerChannel(channelName))
        {
            Notifyer::notifyError(client, 403);
            return ;
        }
        if (!this->_channelList[channelName]->isMember(client))
        {
            Notifyer::notifyError(client, 442);
            return ;
        }
        else
            Notifyer::notifyBroadcast(this->_channelList[channelName], msg);
    }
    else
    {
        if (!this->hasServerClient(target))
        {
            Notifyer::notifyError(client, 442);
            return ;
        } 
        else
            Notifyer::sendMsg(this->_clientList[target], msg); 
    }
}

void    Server::handlerPart(Client* client, std::string& channelName, std::string& msg)
{
    if (!this->hasServerChannel(channelName))
    {
        Notifyer::notifyError(client, 403);
        return ;
    }
    if (!this->_channelList[channelName]->isMember(client))
    {
        Notifyer::notifyError(client, 442);
        return ;
    }
    else
    {
        std::string channel = "#" + channelName;
        this->_channelList[channelName]->removeUser(client);
        if (!msg.empty())
            handlerPrivmsg(client, channel, msg);
    }
}

void    Server::handlerKick(Client* client, std::string& channelName, std::string& targetUser)
{
    if (!this->hasServerChannel(channelName))
    {
        Notifyer::notifyError(client, 403);
        return ;
    }
    if (!this->_channelList[channelName]->isMember(client))
    {
        Notifyer::notifyError(client, 442);
        return ;
    }
    if (!this->_channelList[channelName]->isOperator(client))
    {
        Notifyer::notifyError(client, 482);
        return ;
    }
    if (!this->hasServerClient(targetUser))
    {
        Notifyer::notifyError(client, 444);
        return ;
    }
    if (!this->_channelList[channelName]->isMember(this->_clientList[targetUser]))
    {
        Notifyer::notifyError(client, 445);
        return ;
    }
    this->_channelList[channelName]->kickUser(this->_clientList[targetUser]);
}