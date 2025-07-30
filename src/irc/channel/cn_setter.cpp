/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_setter.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 00:32:55 by siuol             #+#    #+#             */
/*   Updated: 2025/07/30 22:49:24 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

int    Channel::setTopic(const std::string& topic)
{
    this->_topic = topic;
    return -1;
}

int    Channel::setPassword(const std::string& password)
{
    if (password.empty())
        return 484;
    this->_password = password;
    return -1;
}

int    Channel::setOperator(Client* user)
{
    if (user == nullptr)
        return 446;
    if (this->_operator != nullptr)
        return 451;
    else
    {
        this->_operator = user;
        LOG_SUCCESS("[CHANNEL] : Channel is now operated by : ");
        std::cout << this->_operator->getNickName() <<std::endl;
    }
    return -1;
}

int    Channel::setInviteStatus(const bool& status)
{
    if (this->_onlyInvite && status)
        return 454;
    else if (!this->_onlyInvite && !status)
        return 455;
    else
        this->_onlyInvite = status;
    return -1;
}

int    Channel::setLimit(const unsigned int& limit)
{
    if (limit > LIMIT_MEMBER)
        return 456;
    else
        this->_limit = limit;
    return -1;
}

int     Channel::setTopicRight()
{
    if (this->_topicRight)
        return 454;
    this->_topicRight = true;
    return -1;
}