/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseGeneral.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:47:44 by siuol             #+#    #+#             */
/*   Updated: 2025/08/07 22:34:06 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

// void    Server::parseQuit(Client* client, std::string& cmd)
// {
//     std::string msg;

//     std::vector<std::string>cmdPack = parseSplit(cmd);
//     if (client->getStatus() != COMPLETE)
//     {
//         this->removeClient(client->getSocket(), );
//         return ;
//     }
//     msg += (cmdPack.size() < 2 ? "" : cmdPack[1]);
    
//     for (auto& pair : this->_channelList)
//     {
//         Channel* channel = pair.second;
//         std::string channelName = "#" + channel->getChannelName();

//         if (channel->isMember(client))
//             this->handlerPart(client, channelName, msg);
//     }
// }

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
    // if (cmdPack[0] == "QUIT")
    //     this->parseQuit(client, command);
    if (client->getStatus() != COMPLETE)
    {
        this->parseSign(client, command);
        return ;
    }
    else
    {
        execCommand(client, cmdPack[0], command);
        return ;
    }
}