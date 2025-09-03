/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverValidation.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:48:25 by siuol             #+#    #+#             */
/*   Updated: 2025/09/03 09:28:06 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

bool    Server::isServerChannel(Channel* channel)
{
    return (this->_channelList.count(channel->getChannelName()));
}

bool    Server::hasServerChannel(std::string& channelName)
{
    return (this->_channelList.count(channelName));
}

bool    Server::isServerClient(Client* client)
{
    return (this->_clientList.count(client->getUserName()));
}

bool    Server::hasServerClient(std::string& clientName)
{
    return (this->_clientList.count(clientName));
}

void    Server::validateRegistration(Client* client, std::string &nickname)
{
    if (!nickname.empty() && this->hasServerClient(nickname))
    {
        client->setNickName("");
        client->setNickStatus(false);
        Notifyer::notifyError(client, 433);
        return ;
    }
    if (client->getPasswordStatus() && client->getNickStatus() && client->getUserStatus())
        this->_clientList.insert({client->getNickName(), client});
}

bool    Server::validateChannel(Client* client, std::string& channelName)
{
    if (!this->hasServerChannel(channelName))
    {
        Notifyer::notifyError(client, 403);
        return false;
    }
    if (!this->_channelList[channelName]->isMember(client))
    {
        Notifyer::notifyError(client, 442);
        return false;
    }
    return true;
}

bool    Server::validateOperator(Client* client, std::string& channelName)
{
    if (!validateChannel(client, channelName))
        return false;
    if (!this->_channelList[channelName]->isOperator(client))
    {
        Notifyer::notifyError(client, 482);
        return false;
    }
    return true;
}

bool    Server::validateTargetOut(Client* client, std::string& channelName, std::string& target)
{
    if (!this->hasServerClient(target))
    {
        Notifyer::notifyError(client, 444);
        return false;
    }
    if (!this->_channelList[channelName]->isMember(this->_clientList[target]))
    {
        Notifyer::notifyError(client, 445);
        return false;
    }
    return true;
}

bool    Server::validateTargetIn(Client* client, std::string& channelName, std::string& target)
{
    if (!this->hasServerClient(target))
    {
        Notifyer::notifyError(client, 444);
        return false;
    }
    if (this->_channelList[channelName]->isMember(this->_clientList[target]))
    {
        Notifyer::notifyError(client, 441);
        return false;
    }
    return true;
}