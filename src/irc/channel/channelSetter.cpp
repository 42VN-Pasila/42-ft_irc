/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelSetter.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 00:32:55 by siuol             #+#    #+#             */
/*   Updated: 2025/09/12 10:33:35 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

int    Channel::setTopic(const std::string& topic)
{
    this->_topic = topic;
    return -1;
}

int    Channel::setPassword(Client* user, const std::string& password, std::string& channel)
{
    if (password.empty())
    {
        Notifyer::notifyWindowError(user, 484, channel);
        return 484;
    }
    if (!Channel::isValidPassword(password))
    {
        Notifyer::notifyWindowError(user, 487, channel);
        return 487;
    }
    this->_password = password;
    return -1;
}

int    Channel::setOperator(Client* user, std::string& channel)
{
    if (this->isOperator(user))
    {
        Notifyer::notifyWindowError(user, 451, channel);
        return 451;
    }
    else
        this->_operators.insert({user->getNickName(), user});
    return -1;
}

int    Channel::setInviteStatus(Client* user, const bool& status, std::string& channel)
{
    if (this->_onlyInvite && status)
    {
        Notifyer::notifyWindowError(user, 454, channel);
        return 454;
    }
    else if (!this->_onlyInvite && !status)
    {
        Notifyer::notifyWindowError(user, 455, channel);
        return 455;
    }
    else
        this->_onlyInvite = status;
    return -1;
}

int    Channel::setLimit(Client* user, const unsigned int& limit, std::string& channel)
{
    if (limit > LIMIT_MEMBER)
    {
        Notifyer::notifyWindowError(user, 456, channel);
        return 456;
    }
    else
        this->_limit = limit;
    return -1;
}

int     Channel::setTopicRight(Client* user, std::string& channel)
{
    if (this->_topicRight)
    {
        Notifyer::notifyWindowError(user, 449, channel);
        return 449;
    }
    this->_topicRight = true;
    return -1;
}