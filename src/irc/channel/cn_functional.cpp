/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_functional.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 02:03:53 by siuol             #+#    #+#             */
/*   Updated: 2025/07/26 03:02:41 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Channel::addUser(const Client* user)
{
    if (user == nullptr)
    {
        LOG_WARNING("[CHANNEL] : User cannot be null");
        std::cout << std::endl;
        return ;
    }
    if (this->isMember(user))
    {
        LOG_WARNING("[CHANNEL] : User is already in the channel");
        std::cout << std::endl;
        return;
    }
    if  (!this->isAvailable())
    {
        LOG_WARNING("[CHANNEL] : Channel is full");
        std::cout << std::endl;
        return ;
    }
    if  (this->isInviteOnly() &&  !this->isInvited(user))
    {
        LOG_WARNING("[CHANNEL] : User does not have an invitation");
        std::cout << std::endl;
        return ;
    }
    if  (this->isInviteOnly() &&  this->isInvited(user))
        this->_invitation.erase(user->getUserName());
    this->_members.insert({user->getUserName(),const_cast<Client*>(user)});
    LOG_SUCCESS("[CHANNEL] : Welcome ");
    std::cout << user->getUserName();
    LOG_SUCCESS(" to the channel");
    std::cout << std::endl;
    
}

void    Channel::kickUser(const Client* user)
{
    if (user == nullptr)
    {
        LOG_WARNING("[CHANNEL] : User cannot be null");
        std::cout << std::endl;
        return ;
    }
    if (!this->isMember(user))
    {
        LOG_WARNING("[CHANNEL] : User is not in the channel");
        std::cout << std::endl;
        return ;
    }
    this->_members.erase(user->getUserName());
        LOG_SUCCESS("[CHANNEL] : ");
    std::cout << user->getUserName();
    LOG_SUCCESS(" is removed out of the channel");
    std::cout << std::endl;
}

void    Channel::removeOperator()
{
    if (this->_operator == nullptr)
    {
        LOG_WARNING("[CHANNEL] : Channel is not operated by any clients");
        std::cout << std::endl;
        return ;
    }
    this->_operator = nullptr;
    LOG_SUCCESS("[CHANNEL] : Channel now has no operator");
    std::cout << std::endl;
}

void    Channel::inviteUser(const Client* user)
{
    if (user == nullptr)
    {
        LOG_WARNING("[CHANNEL] : User cannot be null");
        std::cout << std::endl;
        return ;
    }
    if (!this->_onlyInvite)
    {
        LOG_WARNING("[CHANNEL] : Channel is not invited_only mode");
        std::cout << std::endl;
        return ;
    }
    if (this->isInvited(user))
    {
        LOG_WARNING("[CHANNEL] : User is already invited");
        std::cout << std::endl;
        return ;
    }
    if (this->isMember(user))
    {
        LOG_WARNING("[CHANNEL] : User is already a member");
        std::cout << std::endl;
        return ;
    }
    this->_invitation.insert({user->getUserName(),const_cast<Client*>(user)});
    LOG_SUCCESS("[CHANNEL] : User is invited");
    std::cout << std::endl;
}