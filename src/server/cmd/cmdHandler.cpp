/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:54 by siuol             #+#    #+#             */
/*   Updated: 2025/08/18 01:00:41 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::handlerJoin(Client* client, std::string& channel, std::string& pass)
{
    int code;
    int subCode;
    
    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }
    std::string channelName = channel.substr(1);
    
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
        std::string msg = "[CHANNEL " + channelName + "]: Welcome " + client->getNickName() + " to the channel";
        Notifyer::notifyBroadcast(this->_channelList[channelName], msg);
        Notifyer::sendMsg(client, this->_channelList[channelName]->getTopic());
        
    }
    else
        Notifyer::notifyError(client, code);  
}

void    Server::handlerPrivmsg(Client* client, std::string& target, std::string& msg)
{
    msg += "\r\n";
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

void    Server::handlerPart(Client* client, std::string& channel, std::string& noti)
{
    int code;
    
    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }
    std::string channelName = channel.substr(1);
    
    if (!validateChannel(client, channelName))
        return ;
    else
    {
        code = this->_channelList[channelName]->removeUser(client);
        if (code == -1)
        {
            std::string msg = client->getNickName() + " has been kicked out of the channel by ";
            std::string privmsg = "[CHANNEL " + channelName + "] : You have left the channel";
            if (!noti.empty())
            {
                msg = msg + " because " + noti;
                privmsg  = privmsg + " because " + noti;
            }
            Notifyer::notifyBroadcast(this->_channelList[channelName], msg);
            privmsg  = RED + privmsg + RESET + "\r\n";
            Notifyer::sendMsg(this->_clientList[client->getNickName()], privmsg);
        }
        else
        {
            Notifyer::notifyError(client, code); 
            return ;
        }
    }
}

void    Server::handlerKick(Client* client, std::string& channel, std::string& targetUser, std::string& reason)
{
    int code;

    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }
    std::string channelName = channel.substr(1);
    
    if (!validateOperator(client, channelName))
        return ;
    if (!validateTarget(client, channelName, targetUser))
        return ;
    code = this->_channelList[channelName]->kickUser(this->_clientList[targetUser]);
    if (code == -1)
    {
        std::string msg = targetUser + " has been kicked out of the channel by " + client->getNickName();
        std::string privmsg = "[CHANNEL " + channelName + "] : You have been kicked out of the channel";
        if (!reason.empty())
        {
            msg = msg + " because " + reason;
            privmsg  = privmsg + " because " + reason;
        }
        Notifyer::notifyBroadcast(this->_channelList[channelName], msg);
        privmsg  = RED + privmsg + RESET + "\r\n";
        Notifyer::sendMsg(this->_clientList[targetUser], privmsg);
    }
    else
    {
        Notifyer::notifyError(client, code);
        return ;
    }
}

void    Server::handlerTopic(Client* client, std::string& channel, std::string& topic)
{
    int code;
    
    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }    
    std::string channelName = channel.substr(1);
    topic = topic.substr(1);
    
    if (!validateChannel(client, channelName))
        return ;
    if (topic.empty())
    {
        std::string currentTopic = this->_channelList[channelName]->getTopic();
        if (currentTopic.empty())
            Notifyer::sendMsg(client, "[SERVER] : [CHANNEL] : Topic : [empty]");
        else
            Notifyer::sendMsg(client, "[SERVER] : [CHANNEL] : Topic : " + currentTopic);
        return ;
    }
    if (this->_channelList[channelName]->isTopicRight())
    {
        if (!validateOperator(client, channelName))
            return ;   
    }
    code = this->_channelList[channelName]->setTopic(topic);
    std::string msg = "Topic : " + topic;
    Notifyer::notifyBroadcast(this->_channelList[channelName], msg);
}

void    Server::handlerInvite(Client* client, std::string& targetUser, std::string& channel)
{
    int code;

    if (channel[0] != '#')
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }
    std::string channelName = channel.substr(1);
    
    if (!validateOperator(client, channelName))
        return ;
    if (!validateTarget(client, channelName, targetUser))
        return ;
    code = this->_channelList[channelName]->inviteUser(this->_clientList[targetUser]);
    if (code == -1)
    {
        std::string msg = "[SERVER] : [CHANNEL] " + channelName + " send you an invitation from "
                                                                + client->getNickName();
        Notifyer::sendMsg(this->_clientList[targetUser], msg);                             
    }
    else
        Notifyer::notifyError(client, code);
}