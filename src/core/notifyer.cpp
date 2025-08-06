/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifyer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:14:07 by siuol             #+#    #+#             */
/*   Updated: 2025/08/06 19:30:48 by caonguye         ###   ########.fr       */
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
        std::cout << std::endl;
    }
    
    ssize_t sent = send(socket, msg.c_str(), msg.length(), 0);
    
    if (sent != -1)
    {
        std::string error = "[SERVER] : Failed to send message from " + client->getNickName();
        LOG_WARNING(error);
        std::cout << std::endl;
    }
    if (sent != static_cast<ssize_t>(msg.length()))
    {
        std::string error = "[SERVER] : Failed to send full of message from " + client->getNickName();
        LOG_WARNING(error);
        std::cout << std::endl;
    }
}

void    Notifyer::notifySuccess(Client* client, const std::string& msg)
{
    std::string message = "[SERVER] : [" + client->getNickName() + "] " + msg;

    sendMsg(client, GREEN + message + RESET);    
}

void    Notifyer::notifyError(Client* client, int code)
{
    std::string message = "[SERVER] :" + std::to_string(code) + ": ["
                        + client->getNickName() + "] " + Notifyer::_notifyCode[code];
    
    sendMsg(client, YELLOW + message + RESET);                    
}

void    Notifyer::notifyBroadcast(Channel* channel, const std::string& msg)
{
    std::string message = "[SERVER] : [" + channel->getChannelName() + "] :" + msg;
    
    for (auto& pair : channel->getMemberList())
        sendMsg(pair.second, CYAN + message + RESET);
}