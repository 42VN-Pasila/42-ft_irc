/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdModeHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:03:37 by caonguye          #+#    #+#             */
/*   Updated: 2025/09/13 08:27:37 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::handlerModeI(Client* client, std::string& channel, bool mode)
{
    int         code;
    std::string msg;
    std::string nickname = client->getNickName();
    
    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }
    
    std::string channelName = channel.substr(1);
    
    if (!this->hasServerChannel(channelName))
    {
        Notifyer::notifyError(client, 450); 
        return ;
    }    

    if (!validateOperator(client, channelName))
        return ;
    code = this->_channelList[channelName]->setInviteStatus(client, mode, channel);
    if (code == -1)
    {
        msg = (mode == on ? "[SERVER] : [CHANNEL] : Invite-only mode enabled" 
                            : "[SERVER] : [CHANNEL] : Invite-only mode disabled");
        Notifyer::notifyBroadcast(this->_channelList[channelName], nickname, msg);
    }
    else     
        return;
}

void    Server::handlerModeT(Client* client, std::string& channel, bool mode)
{
    int         code;
    std::string msg;
    std::string nickname = client->getNickName();
    
    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }
      
    std::string channelName = channel.substr(1);

    if (!this->hasServerChannel(channelName))
    {
        Notifyer::notifyError(client, 450); 
        return ;
    }
    
    if (!validateOperator(client, channelName))
        return ;
    if (mode == on)
        code = this->_channelList[channelName]->setTopicRight(client, channel);
    else
        code = this->_channelList[channelName]->unsetTopicRight(client, channel);
    if (code == -1)
    {
        msg = (mode == on ? "[SERVER] : [CHANNEL] : Topic mode enabled only for operator" 
                            : "[SERVER] : [CHANNEL] : Topic mode enabled for all members");
        Notifyer::notifyBroadcast(this->_channelList[channelName], nickname, msg);
    }
    else     
        return;
}

void    Server::handlerModeK(Client* client, std::string& channel, const std::string& pass, bool mode)
{
    int         code;
    std::string msg;
    std::string nickname = client->getNickName();
    
    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }
     
    std::string channelName = channel.substr(1);

    if (!this->hasServerChannel(channelName))
    {
        Notifyer::notifyError(client, 450); 
        return ;
    }
    
    if (!validateOperator(client, channelName))
        return ;
    if (mode == on)
        code = this->_channelList[channelName]->setPassword(client, pass, channel);
    else
        code = this->_channelList[channelName]->unsetPassword(client, channel);
    if (code == -1)
    {
        msg = (mode == on ? "[SERVER] : [CHANNEL] : New password is set"
                            : "[SERVER] : [CHANNEL] : Password is removed");
        Notifyer::notifyBroadcast(this->_channelList[channelName], nickname, msg);
    }
    else     
        return;
}

void    Server::handlerModeL(Client* client, std::string& channel, const unsigned int limit, bool mode)
{
    int         code;
    std::string msg;
    std::string nickname = client->getNickName();
    
    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }    
    
    std::string channelName = channel.substr(1);

    if (!this->hasServerChannel(channelName))
    {
        Notifyer::notifyError(client, 450); 
        return ;
    }
    
    if (!validateOperator(client, channelName))
        return ;
    if (mode == on)
        code = this->_channelList[channelName]->setLimit(client, limit, channel);
    else
        code = this->_channelList[channelName]->unsetLimit(client, channel);
    if (code == -1)
    {
        msg = (mode == on ? "[SERVER] : [CHANNEL] : Channel now limits only " + std::to_string(limit) + " members"
        : "[SERVER] : [CHANNEL] : Channel now has no limit on member list");
        Notifyer::notifyBroadcast(this->_channelList[channelName], nickname, msg);
    }
    else     
        return;
    
}

void    Server::handlerModeO(Client* client, std::string& channel, std::string& targetUser, bool mode)
{
    int code = -1;
    std::string msg;
    std::string nickname = client->getNickName();
    
    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }    
    
    std::string channelName = channel.substr(1);

    if (!this->hasServerChannel(channelName))
    {
        Notifyer::notifyError(client, 450); 
        return ;
    }

    if (!validateChannel(client, channelName))
        return ;
    if (!validateOperator(client, channelName))
        return ;
    if (!validateTargetOut(client, channelName, targetUser))
        return ;
    if (mode == on)
        code = this->_channelList[channelName]->setOperator(this->_clientList[targetUser], channel);
    else
        code = this->_channelList[channelName]->removeOperator(this->_clientList[targetUser], channel);
    if (code == -1)
    {
        msg = (mode == on ? "[SERVER] : [CHANNEL] : Channel is now operated by " + targetUser
                            : "[SERVER] : [CHANNEL] : Channel is now not operated");
        Notifyer::notifyBroadcast(this->_channelList[channelName], nickname, msg);
    }
    else     
        Notifyer::notifyWindowError(client, code, channel);
}