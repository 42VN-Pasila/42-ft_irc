/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cmd_execution.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:54 by siuol             #+#    #+#             */
/*   Updated: 2025/07/25 11:12:51 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::cmdJoin(Client* client, std::string& channelName)
{
    if (!this->isServerClient(client))
    {
        LOG_WARNING("[SERVER] : Client is not in server");
        std::cout << std::endl;
        return;
    }
    if (!this->isServerChannelName(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in server");
        std::cout << std::endl;
        return;
    }
    
}