/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_validation.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:48:25 by siuol             #+#    #+#             */
/*   Updated: 2025/07/25 11:15:41 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

bool    Server::isServerChannel(const Channel* channel)
{
    return (this->_channelList.count(const_cast<Channel*>(channel)));
}

bool    Server::isServerClient(const Client* client)
{
    return (this->_clientList.count(const_cast<Client*>(client)));
}

bool    Server::isServerChannelName(std::string& name)
{
    for (Channel* channel : this->_channelList)
    {
        if (name == channel->getChannelName())
            return (1);
    }
    return (0);
}