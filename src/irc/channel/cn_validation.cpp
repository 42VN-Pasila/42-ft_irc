/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_validation.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:21:55 by siuol             #+#    #+#             */
/*   Updated: 2025/07/29 14:18:11 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

int    Channel::isOperator(Client* user)
{
    if (user == nullptr)
        return 446;
    return (this->_operator == user);
}

int    Channel::isMember(Client* user)
{
    if (user == nullptr)
        return 446;
    return (this->_members.count(user->getNickName()));
}

int    Channel::isInvited(Client* user)
{
    if (user == nullptr)
        return 446;
    return  (this->_invitation.count(user->getNickName()));
}

bool    Channel::isRequiredPassword()
{
    return (!this->_password.empty());
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

