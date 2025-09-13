/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelUnsetter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 01:02:43 by siuol             #+#    #+#             */
/*   Updated: 2025/09/13 08:26:19 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

int    Channel::unsetTopic()
{
    this->_topic = "";
    return -1;
}

int    Channel::unsetPassword(Client* client, std::string& channel)
{
    if (this->_password.empty())
    {
        Notifyer::notifyWindowError(client, 484, channel);
        return 484;
    }
    this->_password = "";
    return -1;
}

int    Channel::unsetLimit(Client* client, std::string& channel)
{
    if (this->_limit == 0)
    {
        Notifyer::notifyWindowError(client, 459, channel);
        return 459;
    }
    this->_limit = 0;
    return -1;
}

int    Channel::unsetTopicRight(Client* client, std::string& channel)
{
    if (!this->_topicRight)
    {
        Notifyer::notifyWindowError(client, 453, channel);
        return 453;
    }
    this->_topicRight = false;
    return -1;
}
