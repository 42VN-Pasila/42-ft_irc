/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelGetter.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 23:17:53 by siuol             #+#    #+#             */
/*   Updated: 2025/09/11 09:08:35 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

const std::string& Channel::getTopic() const
{
    return this->_topic;   
}

const std::string&   Channel::getPassword() const
{
    return this->_password;
}

const std::string&  Channel::getChannelName() const
{
    return this->_channelName;
}

unsigned int  Channel::getLimit() const
{
    return  this->_limit;
}

bool  Channel::getInviteStatus() const
{
    return this->_onlyInvite;
}

unsigned int  Channel::getQuantity() const
{
    return this->_members.size();
}

const std::map<std::string, Client*>& Channel::getMemberList() const
{
    return this->_members;
}