/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseSignin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:39:35 by siuol             #+#    #+#             */
/*   Updated: 2025/09/03 22:37:25 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::parseSignUSER(Client* client, std::vector<std::string> command)
{
    if (client->getUserStatus())
    {
        Notifyer::notifyError(client, 392);
        return ;
    }
    if (command.size() < 5)
    {
        Notifyer::notifyError(client, 418);
        return ;
    }
    client->setUserName(command[1]);
    std::string realName = "";
    for (size_t i = 4; i < command.size(); i++)
    {
        if (i == 4)
        {
            if (command[i][0] != ':' || command[i].length() == 1)
            {
                Notifyer::notifyError(client, 418); 
                return ;
            }
            realName += command[i].substr(1);
        }
        else
            realName = realName + " " + command[i];
    }
    client->setRealName(realName);
    client->setUserStatus(true);
    std::string nickname = client->getNickName();
    this->validateRegistration(client, nickname);
}

void    Server::parseSignNICK(Client* client, std::vector<std::string> command)
{
    if (client->getNickStatus())
    {
        std::cout << "DEBUG: Nick already set" << std::endl;
        Notifyer::notifyError(client, 391);
        return ;
    }
    if (command.size() != 2)
    {
        Notifyer::notifyError(client, 417);
        return ;
    }
    if (this->hasServerClient(command[1]))
    {
        Notifyer::notifyError(client, 433);
        return ;
    }
    client->setNickName(command[1]);
    client->setNickStatus(true);
    std::string nickname = client->getNickName();
    this->validateRegistration(client, nickname);
}

void    Server::parseSignPASS(Client* client, std::vector<std::string> command)
{
    if (client->getPasswordStatus())
    {
        Notifyer::notifyError(client, 390);
        return ;
    }
    if (command.size() != 2)
    {
        Notifyer::notifyError(client, 415);
        return ;
    }
    if (this->getPass() != command[1])
    {
        Notifyer::notifyError(client, 416);
        return ;
    }
    client->setPasswordStatus(true);
    std::string nickname = client->getNickName();
    this->validateRegistration(client, nickname);
}

void    Server::parseSign(Client* client, std::string& cmd)
{
    std::vector<std::string>    command  = parseSplit(cmd);
    
    if (command[0] == "CAP")
    {
        if (command.size() >= 2 && command[1] == "LS")
        {
            Notifyer::sendMsg(client, ":localhost CAP * LS :\r\n");
        }
        return;
    }
    if (command[0] == "PING" || command[0] == "PONG" || command[0] == "VERSION" || command[0] == "JOIN")
        return;
    if (command[0] == "PASS")
        this->parseSignPASS(client, command);
    else if (command[0] == "NICK")
        this->parseSignNICK(client, command);
    else if (command[0] == "USER")
        this->parseSignUSER(client, command);
    else
    {
        if (!client->getPasswordStatus())
            Notifyer::notifyError(client, 393);
        if (!client->getNickStatus())
            Notifyer::notifyError(client, 394);
        if (!client->getUserStatus())
            Notifyer::notifyError(client, 395);
    }
    return;
}

void    Server::parsePing(Client* client, std::string& fullCommand)
{
    std::vector<std::string> cmdPack = parseSplit(fullCommand);
    std::string msg = ":localhost PONG localhost";
        
    if (cmdPack.size() > 1)
        msg += " :" + cmdPack[1];
    msg += "\r\n";
        
    Notifyer::sendMsg(client, msg);
}