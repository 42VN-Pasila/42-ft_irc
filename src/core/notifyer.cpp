/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifyer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:14:07 by siuol             #+#    #+#             */
/*   Updated: 2025/07/28 14:10:07 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Notifyer::sendMsg(Client* client, const std::string& msg)
{
    int socket = client->getSocket();
    
    if (socket < 0)
    {
        std::string error = "[SERVER] : " + client->getNickName() + 
                            " is not connected to the server socket";
        LOG_WARNING(error);    
    }
}

void    Notifyer::notifySuccess(Client* client, int code, const std::string& msg)
{
    std::string message = "[SERVER] :" + std::to_string(code) + ": ["
                        + client->getNickName() + "] " + msg + RESET;

    sendMsg(client, GREEN + message);    
}

void    Notifyer::notifyError(Client* client, int code, const std::string& msg)
{
    std::string message = "[SERVER] :" + std::to_string(code) + ": ["
                        + client->getNickName() + "] " + msg + RESET;
    
    sendMsg(client, YELLOW + message);                    
}

void    Notifyer::notifyBroadcast(Channel* channel, const std::string& msg)
{
    std::string message = ":irc.server " + channel->getChannelName() + " " + msg + RESET;
    
    for (auto& pair : channel->getMemberList())
    {
        
    }
}