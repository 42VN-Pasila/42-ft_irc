/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_validation.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:21:55 by siuol             #+#    #+#             */
/*   Updated: 2025/07/25 11:27:58 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

bool    Channel::isOperator(const Client* user)
{
    if (user == nullptr)
    {
        LOG_WARNING("[CHANNEL] : User cannot be null");
        std::cout << std::endl;
        return false;
    }
    return (this->_operator == user);
}

bool    Channel::isMember(const Client* user)
{
    if (user == nullptr)
    {
        LOG_WARNING("[CHANNEL] : User cannot be null");
        std::cout << std::endl;
        return false;
    }
    return (this->_members.count(user->getUserName()));
}

bool    Channel::isInvited(const Client* user)
{
    if (user == nullptr)
    {
        LOG_WARNING("[CHANNEL] : User cannot be null");
        std::cout << std::endl;
        return false;
    }
    return  (this->_invitation.count(user->getUserName()));
}

bool    Channel::isInviteOnly()
{
    return (this->_onlyInvite);
}

bool    Channel::isEmpty()
{
    return (this->_members.size() == 0);
}

bool   Channel::isAvailable()
{
    if (this->_limit == 0)
        return true;
    return (this->_members.size() < this->_limit);
}

