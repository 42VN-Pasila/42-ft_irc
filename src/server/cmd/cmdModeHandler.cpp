/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdModeHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:03:37 by caonguye          #+#    #+#             */
/*   Updated: 2025/09/06 11:34:30 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::handlerModeI(Client* client, std::string& channel, bool mode)
{
    int         code;
    std::string msg;
    
    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }    
    std::string channelName = channel.substr(1);
    
    if (!validateOperator(client, channelName))
        return ;
    code = this->_channelList[channelName]->setInviteStatus(mode);
    if (code == -1)
    {
        msg = (mode == on ? "[SERVER] : [CHANNEL] : Invite-only mode enabled" 
                            : "[SERVER] : [CHANNEL] : Invite-only mode disabled");
        Notifyer::notifyBroadcast(this->_channelList[channelName], msg, client->getNickName());
    }
    else     
        Notifyer::notifyError(client, code);
}

void    Server::handlerModeT(Client* client, std::string& channel, bool mode)
{
    int         code;
    std::string msg;
    
    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }    
    std::string channelName = channel.substr(1);
    if (!validateOperator(client, channelName))
        return ;
    if (mode == on)
        code = this->_channelList[channelName]->setTopicRight();
    else
        code = this->_channelList[channelName]->unsetTopicRight();
    if (code == -1)
    {
        msg = (mode == on ? "[SERVER] : [CHANNEL] : Topic mode enabled only for operator" 
                            : "[SERVER] : [CHANNEL] : Topic mode enabled for all members");
        Notifyer::notifyBroadcast(this->_channelList[channelName], msg, client->getNickName());
    }
    else     
        Notifyer::notifyError(client, code);
}

void    Server::handlerModeK(Client* client, std::string& channel, const std::string& pass, bool mode)
{
    int         code;
    std::string msg;
    
    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }    
    std::string channelName = channel.substr(1);
    if (!validateOperator(client, channelName))
        return ;
    if (mode == on)
        code = this->_channelList[channelName]->setPassword(pass);
    else
        code = this->_channelList[channelName]->unsetPassword();
    if (code == -1)
    {
        msg = (mode == on ? "[SERVER] : [CHANNEL] : New password is set"
                            : "[SERVER] : [CHANNEL] : Password is removed");
        Notifyer::notifyBroadcast(this->_channelList[channelName], msg, client->getNickName());
    }
    else     
        Notifyer::notifyError(client, code);
}

void    Server::handlerModeL(Client* client, std::string& channel, const unsigned int limit, bool mode)
{
    int         code;
    std::string msg;
    
    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }    
    std::string channelName = channel.substr(1);
    if (!validateOperator(client, channelName))
        return ;
    if (mode == on)
        code = this->_channelList[channelName]->setLimit(limit);
    else
        code = this->_channelList[channelName]->unsetLimit();
    if (code == -1)
    {
        msg = (mode == on ? "[SERVER] : [CHANNEL] : Channel now limits only " + std::to_string(limit) + " members"
        : "[SERVER] : [CHANNEL] : Channel now has no limit on member list");
        Notifyer::notifyBroadcast(this->_channelList[channelName], msg, client->getNickName());
    }
    else     
        Notifyer::notifyError(client, code);
    
}

void    Server::handlerModeO(Client* client, std::string& channel, std::string& targetUser, bool mode)
{
    int code = -1;
    std::string msg;
    
    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }    
    std::string channelName = channel.substr(1);
    if (!validateChannel(client, channelName))
        return ;
    if (!validateOperator(client, channelName))
        return ;
    if (!validateTargetOut(client, channelName, targetUser))
        return ;
    if (mode == on)
        code = this->_channelList[channelName]->setOperator(this->_clientList[targetUser]);
    else
        code = this->_channelList[channelName]->removeOperator(this->_clientList[targetUser]);
    if (code == -1)
    {
        msg = (mode == on ? "[SERVER] : [CHANNEL] : Channel is now operated by " + targetUser
                            : "[SERVER] : [CHANNEL] : Channel is now not operated");
        Notifyer::notifyBroadcast(this->_channelList[channelName], msg, client->getNickName());
    }
    else     
        Notifyer::notifyError(client, code);
}