/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelFunctional.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 02:03:53 by siuol             #+#    #+#             */
/*   Updated: 2025/09/09 01:03:07 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

int    Channel::addUser(Client* user, std::string &channel)
{
    if (this->isMember(user))
    {
        Notifyer::notifyWindowError(user, 443, channel);
        return 443;
    }
    if  (!this->isAvailable())
    {
        Notifyer::notifyChannelError(user, 471, channel);
        return 471;
    }
    if  (this->isInviteOnly() &&  !this->isInvited(user))
    {
        Notifyer::notifyChannelError(user, 473, channel);
        return 473;
    }
    if  (this->isInviteOnly() &&  this->isInvited(user))
        this->_invitation.erase(user->getNickName());
    this->_members.insert({user->getNickName(), user});
    return -1;
}

int    Channel::kickUser(Client* user)
{
    if (user == nullptr)
        return  446;
    if (!this->isMember(user))
        return 442;
    this->_members.erase(user->getNickName());
    return -1;
}

int    Channel::removeOperator(Client* client)
{
    if (this->getOperator() == nullptr)
        return 452;
    if (this->getOperator() != client)
        return 482;
    this->_operator = nullptr;
    return -1;
}

int    Channel::inviteUser(Client* user)
{
    if (user == nullptr)
        return 446;
    if (!this->_onlyInvite)
        return 453;
    if (this->isInvited(user))
        return 448;
    if (this->isMember(user))
        return 443;
    this->_invitation.insert({user->getNickName(),const_cast<Client*>(user)});
    return -1;
}

int    Channel::removeUser(Client* user)
{
    if (user == nullptr)
        return 446;
    if (!this->isMember(user))
        return 442;
    if (this->getOperator() == user)
        this->removeOperator(user);
    this->_members.erase(user->getNickName());
    return -1;
}