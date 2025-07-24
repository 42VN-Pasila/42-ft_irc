/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_setter.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 00:32:55 by siuol             #+#    #+#             */
/*   Updated: 2025/07/25 00:16:41 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Channel::setTopic(const std::string& topic)
{
    this->_topic = topic;
    LOG_SUCCESS("[CHANNEL] : Channel's topic is changed to ");
    std::cout << topic << std::endl;
}

void    Channel::setPassword(const std::string& password)
{
    this->_password = password;
    LOG_SUCCESS("[CHANNEL] : Password is set");
    std::cout << std::endl;
}

void    Channel::setOperator(const Client* user)
{
    if (user == nullptr)
    {
        LOG_WARNING("[CHANNEL] : User cannot be null");
        std::cout << std::endl;
        return ;
    }
    if (this->_operator != nullptr)
    {
        LOG_WARNING("[CHANNEL] : This channel is already being operated by ");
        std::cout << this->_operator->getName() << std::endl;
        return ;
    }
    else
    {
        this->_operator = const_cast<Client*>(user);
        LOG_SUCCESS("[CHANNEL] : Channel is now operated by : ");
        std::cout << this->_operator->getName() <<std::endl;
    }
}

void    Channel::setInviteStatus(const bool& status)
{
    if (this->_onlyInvite && status)
    {
        LOG_WARNING("[CHANNEL] : This channel is already set to only invited mode");
        std::cout << std::endl;
    }
    else if (!this->_onlyInvite && !status)
    {
        LOG_WARNING("[CHANNEL] : This channel is already unset only invited mode");
        std::cout << std::endl;
    }
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

void    Channel::setLimit(const unsigned int& limit)
{
    if (limit > LIMIT_MEMBER)
        LOG_WARNING("[CHANNEL] : Only support 1000 users");
    else
    {
        this->_limit = limit;
        LOG_SUCCESS("[CHANNEL] : Channel limits only ");
        std::cout << std::to_string(limit);
        LOG_SUCCESS(" member(s)");
    }
    std::cout << std::endl;
}