/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_functional.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 02:03:53 by siuol             #+#    #+#             */
/*   Updated: 2025/07/29 14:15:11 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

int    Channel::addUser(Client* user)
{
    if (user == nullptr)
        return 446;
    if (this->isMember(user))
        return 443;
    if  (!this->isAvailable())
        return 471;
    if  (this->isInviteOnly() &&  !this->isInvited(user))
        return 447;
    if  (this->isInviteOnly() &&  this->isInvited(user))
        this->_invitation.erase(user->getNickName());
    this->_members.insert({user->getNickName(),const_cast<Client*>(user)});
    LOG_SUCCESS("[CHANNEL] : Welcome ");
    std::cout << user->getNickName();
    LOG_SUCCESS(" to the channel");
    std::cout << std::endl;
    
}

int    Channel::kickUser(Client* user)
{
    if (user == nullptr)
        return  446;
    if (!this->isMember(user))
        return 442;
    this->_members.erase(user->getNickName());
        LOG_SUCCESS("[CHANNEL] : ");
    std::cout << user->getNickName();
    LOG_SUCCESS(" is removed out of the channel");
    std::cout << std::endl;
}

int    Channel::removeOperator()
{
    if (this->_operator == nullptr)
        return 452;
    this->_operator = nullptr;
    LOG_SUCCESS("[CHANNEL] : Channel now has no operator");
    std::cout << std::endl;
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
    LOG_SUCCESS("[CHANNEL] : User is invited");
    std::cout << std::endl;
}

int    Channel::removeUser(Client* user)
{
    if (user == nullptr)
        return 446;
    if (!this->isMember(user))
        return 442;
    this->_members.erase(user->getNickName());
        LOG_SUCCESS("[CHANNEL] : ");
    std::cout << user->getNickName();
    LOG_SUCCESS(" left the channel");
    std::cout << std::endl;
}