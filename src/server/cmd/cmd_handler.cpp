/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:54 by siuol             #+#    #+#             */
/*   Updated: 2025/07/29 12:56:57 by siuol            ###   ########.fr       */
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
    {
        Notifyer::notifyError(client, 470);
        return ;
    }
    else
        this->_channelList[channelName]->addUser(client);
}

void    Server::handlerPrivmsg(Client* client, std::string& target, std::string& msg)
{
    if (target[0] == '#')
    {
        std::string channelName = target.substr(1);
        if (!validateChannel(client, channelName))
            return ;
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
    if (!validateChannel(client, channelName))
        return ;
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
    if (!validateOperator(client, channelName))
        return ;
    if (!validateTarget(client, channelName, targetUser))
        return ;
    this->_channelList[channelName]->kickUser(this->_clientList[targetUser]);
}