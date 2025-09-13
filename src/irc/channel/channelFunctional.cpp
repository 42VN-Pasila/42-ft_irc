/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelFunctional.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 02:03:53 by siuol             #+#    #+#             */
/*   Updated: 2025/09/13 14:18:24 by caonguye         ###   ########.fr       */
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

int    Channel::kickUser(Client* user, Client* target, std::string& channel)
{
    if (!this->isMember(target))
    {
        Notifyer::notifyWindowError(user, 442, channel);   
        return 442;
    }
    if (this->isOperator(target))
    {
        Notifyer::notifyWindowError(user, 461, channel);
        return 461;
    }
    this->_members.erase(target->getNickName());
    return -1;
}

int    Channel::removeOperator(Client* user, std::string &channel)
{
    if (!this->isOperator(user))
    {
        Notifyer::notifyWindowError(user, 452, channel);
        return 452;
    }
    else
        this->_operators.erase(user->getNickName());
    return -1;
}

int    Channel::inviteUser(Client* user, Client* target, std::string& channel)
{
    if (!this->_onlyInvite)
    {
        Notifyer::notifyWindowError(user, 453, channel);
        return 453;
    }
    if (this->isInvited(target))
    {
        Notifyer::notifyWindowError(user, 448, channel);
        return 448;
    }
    if (this->isMember(target))
    {
        Notifyer::notifyWindowError(user, 443, channel);
        return 443;
    }
    this->_invitation.insert({target->getNickName(),const_cast<Client*>(target)});
    return -1;
}

int    Channel::removeUser(Client* user, std::string& channel)
{
    if (!this->isMember(user))
    {
        Notifyer::notifyError(user, 442);
        return 442;
    }
    if (this->isOperator(user))
        this->removeOperator(user, channel);
    this->_members.erase(user->getNickName());
    return -1;
}