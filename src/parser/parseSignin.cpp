/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_signin.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:39:35 by siuol             #+#    #+#             */
/*   Updated: 2025/08/03 12:44:52 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::prs_signinUSER(Client* client, std::vector<std::string> command)
{
    if (command.size() < 5 || command[0] != "USER")
    {
        Notifyer::notifyError(client, 418);
        return ;
    }
    client->setUserName(command[1]);
    std::string realName = "";
    for (int i = 4; i < command.size(); i++)
    {
        if (i == 4)
            realName += command[i].substr(1);
        else
            realName = realName + " " + command[i];
    }
    client->setRealName(realName);
    client->setStatus(COMPLETE);
}

void    Server::prs_signinNICK(Client* client, std::vector<std::string> command)
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

void    Server::prs_signinPASS(Client* client, std::vector<std::string> command)
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

void    Server::prs_signin(Client* client, std::string cmd)
{
    std::vector<std::string>    command  = split(cmd);
    
    if (client->getStatus() == PASS)
        this->prs_signinPASS(client, command);
    else if (client->getStatus() == NICK)
        this->prs_signinNICK(client, command);
    else if (client->getStatus() == USER)
        this->prs_signinUSER(client, command);
    else
        return ;
}