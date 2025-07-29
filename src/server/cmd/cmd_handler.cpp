/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:54 by siuol             #+#    #+#             */
/*   Updated: 2025/07/29 16:04:56 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::handlerJoin(Client* client, std::string& channelName, std::string& pass)
{
    int code;
    int subCode;
    if (!this->hasServerChannel(channelName))
    {
        Channel* newChannel = new Channel(channelName);
        this->_channelList.insert({channelName, newChannel});
        code = newChannel->addUser(client);
        if (code != -1)
        {
            Notifyer::notifyError(client, code); 
            return ;
        }
        subCode = newChannel->setOperator(client);
        if (subCode != -1)
        {
            Notifyer::notifyError(client, subCode); 
            return ;
        }
    }
    else if (!this->passwordRequired(this->_channelList[channelName], pass))
    {
        Notifyer::notifyError(client, 470);
        return ;
    }
    else
        code = this->_channelList[channelName]->addUser(client); 
    if (code == -1)
    {
        std::string msg = "[SERVER] : Welcome " + client->getNickName() + " to the channel";
        Notifyer::notifyBroadcast(this->_channelList[channelName], msg);
    }
    else
        Notifyer::notifyError(client, code);  
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
    int code;
    
    if (!validateChannel(client, channelName))
        return ;
    else
    {
        std::string channel = "#" + channelName;
        code = this->_channelList[channelName]->removeUser(client);
        if (code == -1)
        {
            std::string msg = "[SERVER] : " + client->getNickName() + " has left the channel";
            Notifyer::notifyBroadcast(this->_channelList[channelName], msg);
        }
        else
        {
            Notifyer::notifyError(client, code); 
            return ;
        }
        if (!msg.empty())
            handlerPrivmsg(client, channel, msg);
    }
}

void    Server::handlerKick(Client* client, std::string& channelName, std::string& targetUser)
{
    int code;
    if (!validateOperator(client, channelName))
        return ;
    if (!validateTarget(client, channelName, targetUser))
        return ;
    code = this->_channelList[channelName]->kickUser(this->_clientList[targetUser]);
    if (code == -1)
    {
        std::string msg = "[SERVER] : " + client->getNickName() + " has been kicked out of the channel";
        Notifyer::notifyBroadcast(this->_channelList[channelName], msg);
    }
    else
        Notifyer::notifyError(client, code);
}