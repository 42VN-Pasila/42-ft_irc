/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverValidation.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:48:25 by siuol             #+#    #+#             */
/*   Updated: 2025/08/24 20:02:09 by caonguye         ###   ########.fr       */
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

bool    Server::validateTarget(Client* client, std::string& channelName, std::string& target)
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