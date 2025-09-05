/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:54 by siuol             #+#    #+#             */
/*   Updated: 2025/09/06 01:29:49 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::handlerJoin(Client* client, std::string& channel, std::string& pass)
{
    int code;
    int subCode;
    
    if (channel[0] != '#' || channel.length() == 1)
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
        Notifyer::notifyBroadcast(client, this->_channelList[channelName], msg);
        if (!this->_channelList[channelName]->getTopic().empty())
        {
            std::string topic = "[CHANNEL]: [TOPIC]: " + this->_channelList[channelName]->getTopic() + "\r\n"; 
            Notifyer::sendMsg(client, CYAN + topic + RESET);
        }
    }
    else
        Notifyer::notifyError(client, code);  
}

void    Server::handlerPrivmsg(Client* client, std::string& target, std::string& msg)
{
    std::cout << "NOTI--" << msg << std::endl;
    std::string confirmation = ":" + client->getNickName() + " PRIVMSG " + target + " " + msg + "\r\n";
    msg = "[" + client->getNickName() + "]: " + msg;

    if (target[0] == '#')
    {
        if (target.length() == 1)
        {
            Notifyer::notifyError(client, 502);
            return ;
        }
        std::string channelName = target.substr(1);
        if (!validateChannel(client, channelName))
            return ;
        else
            Notifyer::notifyBroadcast(client, this->_channelList[channelName], confirmation);
    }
    else
    {
        if (!this->hasServerClient(target))
        {
            Notifyer::notifyError(client, 442);
            return ;
        } 
        else
        {
            msg += "\r\n";
            Notifyer::sendMsg(this->_clientList[target], msg); 
        }
    }
}

void    Server::handlerPart(Client* client, std::string& channel, std::string& noti)
{
    int code;
    
    if (channel[0] != '#' || channel.length() == 1)
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
            std::string msg = client->getNickName() + " has left the channel by ";
            std::string confirmation = ":" + client->getNickName() + " PART #" + channelName; 
            std::string privmsg = "[CHANNEL " + channelName + "] : You have left the channel";
            if (!noti.empty())
            {
                msg = msg + " because " + noti;
                confirmation += " :" + noti;
                privmsg  = privmsg + " because " + noti;
            }
            Notifyer::notifyBroadcast(client, this->_channelList[channelName], msg);
            confirmation += "\r\n";
            privmsg  = RED + privmsg + RESET + "\r\n";
            Notifyer::sendMsg(this->_clientList[client->getNickName()], confirmation);
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

    if (channel[0] != '#' || channel.length() == 1)
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }
    if (client->getNickName() == targetUser)
    {
        Notifyer::notifyError(client , 460);
        return ;
    }
    std::string channelName = channel.substr(1);
    
    if (!validateOperator(client, channelName))
        return ;
    if (!validateTargetOut(client, channelName, targetUser))
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
        Notifyer::notifyBroadcast(client, this->_channelList[channelName], msg);
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
    
    if (channel[0] != '#' || channel.length() == 1)
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }    
    std::string channelName = channel.substr(1);
    if (!topic.empty())
        topic = topic.substr(1);
    
    if (!validateChannel(client, channelName))
        return ;
    if (topic.empty())
    {
        std::string finalTopic;
        std::string currentTopic = this->_channelList[channelName]->getTopic();
        if (currentTopic.empty())
            finalTopic = "[SERVER] : [CHANNEL] : Topic : [empty]";
        else
            finalTopic = "[SERVER] : [CHANNEL] : Topic : " + currentTopic;
        Notifyer::sendMsg(client, CYAN + finalTopic + RESET);
        return ;
    }
    if (this->_channelList[channelName]->isTopicRight())
    {
        if (!validateOperator(client, channelName))
            return ;   
    }
    code = this->_channelList[channelName]->setTopic(topic);
    std::string msg = "Topic : " + topic;
    Notifyer::notifyBroadcast(client, this->_channelList[channelName], msg);
}

void    Server::handlerInvite(Client* client, std::string& targetUser, std::string& channel)
{
    int code;

    if (channel[0] != '#' || channel.length() == 1)
    {
        Notifyer::notifyError(client, 502); 
        return ;
    }
    std::string channelName = channel.substr(1);
    
    if (!validateOperator(client, channelName))
        return ;
    if (!validateTargetIn(client, channelName, targetUser))
        return ;
    code = this->_channelList[channelName]->inviteUser(this->_clientList[targetUser]);
    if (code == -1)
    {
        std::string msg = "[SERVER] : [CHANNEL] " + channelName + " send you an invitation from "
                                                                + client->getNickName() + "\r\n";
        Notifyer::sendMsg(this->_clientList[targetUser], CYAN + msg + RESET);                             
    }
    else
        Notifyer::notifyError(client, code);
}