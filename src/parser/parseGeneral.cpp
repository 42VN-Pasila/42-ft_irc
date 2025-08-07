/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseGeneral.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:47:44 by siuol             #+#    #+#             */
/*   Updated: 2025/08/07 10:56:01 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::execCommand(Client* client, std::string cmd, std::string fullCommand)
{
    if (cmd == "JOIN")
        this->parseJoin(client, fullCommand);
    else if (cmd == "PART" || cmd == "PRIVMSG" || cmd == "KICK")
        this->parseMultiTargets(client, fullCommand);
    else if (cmd == "INVITE")
        this->parseInvite(client, fullCommand);
    else if (cmd == "TOPIC")
        this->parseTopic(client, fullCommand);
    else if (cmd == "MODE")
        this->parseMode(client, fullCommand);
    else
        Notifyer::notifyError(client, 421);
}

void    Server::parseCommand(Client* client, std::string& command)
{
    if (command.empty())
    {
        Notifyer::notifyError(client, 485); 
        return ;
    }
    std::vector<std::string> cmdPack = parseSplit(command);
    if (client->getStatus() != COMPLETE)
        this->parseSign(client, command);
    else
        execCommand(client, cmdPack[0], command);
}