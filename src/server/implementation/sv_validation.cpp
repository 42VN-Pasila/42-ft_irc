/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_validation.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:48:25 by siuol             #+#    #+#             */
/*   Updated: 2025/07/26 03:38:52 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

bool    Server::isServerChannel(const Channel* channel)
{
    return (this->_channelList.count(channel->getChannelName()));
}

bool    Server::hasServerChannel(std::string& channelName)
{
    return (this->_channelList.count(channelName));
}

bool    Server::isServerClient(const Client* client)
{
    return (this->_clientList.count(client->getUserName()));
}

