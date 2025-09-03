/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifyer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:14:07 by siuol             #+#    #+#             */
/*   Updated: 2025/09/04 02:12:09 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Notifyer::sendMsg(Client* client, const std::string& msg)
{
    int socket = client->getSocket();
    
    std::cout << "HERE: " <<msg<<std::endl;
    
    if (socket < 0)
    {
        std::string error = "[SERVER] : " + client->getNickName() + 
                            " is not connected to the server socket\r\n";
        LOG_WARNING(error);
        return ;
    }
    
    ssize_t sent = send(socket, msg.c_str(), msg.length(), 0);
    
    if (sent == -1)
    {
        std::string error = "[SERVER] : Failed to send message from " + client->getNickName() + "\r\n";
        LOG_WARNING(error);
        return ;
    }
    if (sent != static_cast<ssize_t>(msg.length()))
    {
        std::string error = "[SERVER] : Failed to send full of message from " + client->getNickName() + "\r\n";
        LOG_WARNING(error);
        return ;
    }
}

void    Notifyer::notifySuccess(Client* client, const std::string& msg)
{
    std::string message = "[SERVER] : [" + client->getNickName() + "] " + msg + "\r\n";

    sendMsg(client, GREEN + message + RESET);    
}

void    Notifyer::notifyError(Client* client, int code)
{
    std::string message = "[SERVER] :" + std::to_string(code) + ": ["
                        + client->getNickName() + "] " + Notifyer::_notifyCode[code] + "\r\n";
    
    sendMsg(client, YELLOW + message + RESET);                    
}

void    Notifyer::notifyBroadcast(Channel* channel, const std::string& msg)
{
    std::string message = "[SERVER] : [CHANNEL " + channel->getChannelName() + "] :" + msg + "\r\n";
    
    for (auto& pair : channel->getMemberList())
        sendMsg(pair.second, CYAN + message + RESET);
}

void Notifyer::sendWelcome(Client* client)
{
   std::string nickname = client->getNickName();
   std::string username = client->getUserName();
   
   std::string host = getHost();
   
   std::string date = getDate();
   
   std::string msg = ":" + host + RPL_WELCOME + nickname + " :Welcome to the Internet Relay Network " + nickname + "!" + username + "@" + host + "\r\n";
   sendMsg(client, msg);

   msg = ":" + host + RPL_YOURHOST + nickname + " :Your host is " + host + ", running version 1.0\r\n";
   sendMsg(client, msg);
   
   msg = ":" + host + RPL_CREATED + nickname + " :This server was created " + date + "\r\n";
   sendMsg(client, msg);
   
   msg = ":" + host + RPL_MYINFO + nickname + " " + host + " 1.0 io itkol\r\n";
   sendMsg(client, msg);
}

std::string Notifyer::getHost()
{
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    std::string host = hostname;
    return host;
}

std::string Notifyer::getDate()
{
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d %m %Y %H:%M:%S", timeinfo);
    std::string date = buffer;
    return date;
}