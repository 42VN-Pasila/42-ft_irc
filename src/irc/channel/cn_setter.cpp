/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_setter.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 00:32:55 by siuol             #+#    #+#             */
/*   Updated: 2025/07/29 14:33:12 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

int    Channel::setTopic(const std::string& topic)
{
    if (topic.empty())
        return 483;
    this->_topic = topic;
    LOG_SUCCESS("[CHANNEL] : Channel's topic is changed to ");
    std::cout << topic << std::endl;
}

int    Channel::setPassword(const std::string& password)
{
    if (password.empty())
        return 484;
    this->_password = password;
    LOG_SUCCESS("[CHANNEL] : New password is set");
    std::cout << std::endl;
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
}

int    Channel::setInviteStatus(const bool& status)
{
    if (this->_onlyInvite && status)
        return 454;
    else if (!this->_onlyInvite && !status)
        return 455;
    else
    {
        this->_onlyInvite = status;
        if (status)
            LOG_SUCCESS("[CHANNEL] : Invite-only mode enabled");
        else
            LOG_SUCCESS("[CHANNEL] : Invite-only mode disabled");
        std::cout << std::endl;
    }
}

int    Channel::setLimit(const unsigned int& limit)
{
    if (limit > LIMIT_MEMBER)
        return 456;
    else
    {
        this->_limit = limit;
        LOG_SUCCESS("[CHANNEL] : Channel limits only ");
        std::cout << std::to_string(limit);
        LOG_SUCCESS(" member(s)");
    }
    std::cout << std::endl;
}