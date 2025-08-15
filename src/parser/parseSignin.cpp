/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseSignin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:39:35 by siuol             #+#    #+#             */
/*   Updated: 2025/08/15 03:41:29 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::parseSignUSER(Client* client, std::vector<std::string> command)
{
    if (command.size() < 5 || command[0] != "USER")
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
    client->setStatus(COMPLETE);
    this->_clientList.insert({client->getNickName(), client});
}

void    Server::parseSignNICK(Client* client, std::vector<std::string> command)
{
    if (command.size() != 2 || command[0] != "NICK")
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
    client->setStatus(USER);
}

void    Server::parseSignPASS(Client* client, std::vector<std::string> command)
{
    if (command.size() != 2 || command[0] != "PASS")
    {
        Notifyer::notifyError(client, 415);
        return ;
    }
    if (this->getPass() != command [1])
    {
        Notifyer::notifyError(client, 416);
        return ;
    }
    client->setStatus(NICK); 
}

void    Server::parseSign(Client* client, std::string& cmd)
{
    std::vector<std::string>    command  = parseSplit(cmd);
    
    if (client->getStatus() == PASS)
        this->parseSignPASS(client, command);
    else if (client->getStatus() == NICK)
        this->parseSignNICK(client, command);
    else if (client->getStatus() == USER)
        this->parseSignUSER(client, command);
    else
        return ;
}