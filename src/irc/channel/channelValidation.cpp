/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelValidation.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:21:55 by siuol             #+#    #+#             */
/*   Updated: 2025/09/14 10:58:43 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

int    Channel::isOperator(Client* user)
{
    return (this->_operators.count(user->getNickName()));
}

int    Channel::isMember(Client* user)
{
    return (this->_members.count(user->getNickName()));
}

int    Channel::isInvited(Client* user)
{
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

bool   Channel::isTopicRight()
{
    return this->_topicRight;
}

bool   Channel::isValidPassword(std::string pass)
{
    for (char c : pass)
    {
        if (c == '\n' || c == '\t' || c == '\r' || c == ' ' || c == ',' ||
            c == ':' || c == '#' || c == '+' || c == '-')
        return 0;
    }
    return 1;
}