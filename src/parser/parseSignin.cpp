/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseSignin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:39:35 by siuol             #+#    #+#             */
/*   Updated: 2025/09/03 09:18:43 by siuol            ###   ########.fr       */
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
    if (command.size() < 5 || command[0] != "USER" || command[2] != "0" || command[3] != "*")
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
    
    if (command[0] == "PASS")
        this->parseSignPASS(client, command);
    else if (command[0] == "NICK")
        this->parseSignNICK(client, command);
    else if (command[0] == "USER")
        this->parseSignUSER(client, command);
    else
        return ;
}