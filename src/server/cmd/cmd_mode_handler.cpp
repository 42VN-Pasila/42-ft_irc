/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode_handler.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:03:37 by caonguye          #+#    #+#             */
/*   Updated: 2025/07/29 17:04:59 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::handlerModeI(Client* client, std::string& channelName, bool mode)
{
    int         code;
    std::string msg;
    
    if (!validateOperator(client, channelName))
        return ;
    code = this->_channelList[channelName]->setInviteStatus(mode);
    if (code == -1)
    {
        msg = (mode == on ? "[SERVER] : [CHANNEL] : Invite-only mode enabled" : "[SERVER] : [CHANNEL] : Invite-only mode disabled");
        Notifyer::notifyBroadcast(this->_channelList[channelName], msg);
    }
    else     
        Notifyer::notifyError(client, code);
}

void    Server::handlerModeT(Client* client, std::string& channelName, bool mode)
{
    int         code;
    std::string msg;
    
    if (!validateOperator(client, channelName))
        return ;
    if (mode == on)
        code = this->_channelList[channelName]->setTopicRight();
    else
        code = this->_channelList[channelName]->unsetTopicRight();
    if (code == -1)
    {
        msg = (mode == on ? "[SERVER] : [CHANNEL] : Invite-only mode enabled" : "[SERVER] : [CHANNEL] : Invite-only mode disabled");
        Notifyer::notifyBroadcast(this->_channelList[channelName], msg);
    }
    else     
        Notifyer::notifyError(client, code);
}

void    Server::handlerModeK(Client* client, std::string& channelName, const std::string& pass, bool mode)
{
    int         code;
    std::string msg;
    
    if (!validateOperator(client, channelName))
        return ;
    if (mode == on)
        code = this->_channelList[channelName]->setPassword(pass);
    else
        code = this->_channelList[channelName]->unsetPassword();
    if (code == -1)
    {
        msg = (mode == on ? "[SERVER] : [CHANNEL] : New password is set" : "[SERVER] : [CHANNEL] : Password is removed");
        Notifyer::notifyBroadcast(this->_channelList[channelName], msg);
    }
    else     
        Notifyer::notifyError(client, code);
}

void    Server::handlerModeO(Client* client, std::string& channelName, std::string& nickName, bool mode)
{
    if (!this->hasServerChannel(channelName))
    {
        Notifyer::notifyError(client, 403);
        return ;
    } 
}

void    Server::handlerModeL(Client* client, std::string& channelName, const unsigned int limit, bool mode)
{
    int         code;
    std::string msg;
    
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
        Notifyer::notifyBroadcast(this->_channelList[channelName], msg);
    }
    else     
        Notifyer::notifyError(client, code);
    
}
