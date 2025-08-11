/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseGeneral.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:47:44 by siuol             #+#    #+#             */
/*   Updated: 2025/08/11 19:12:22 by htran-th         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::parseQuit(Client* client, std::string& cmd)
{
    std::string msg;
    int fd  = client->getSocket();
    int index = this->getIndex(fd);

    if (index == -1)
    {
        LOG_ERROR("[SERVER] : System cannot find user");
        return;
    }
    std::vector<std::string>cmdPack = parseSplit(cmd);
    if (client->getStatus() != COMPLETE)
    {
        this->removeClient(fd, index);
        return ;
    }
    msg += (cmdPack.size() < 2 ? "" : cmdPack[1]);
    
    for (auto& pair : this->_channelList)
    {
        Channel* channel = pair.second;
        std::string channelName = "#" + channel->getChannelName();
        std::string quitmsg = "[CHANNEL] :" + client->getNickName() +" quit server " + msg;

        if (channel->isMember(client))
            Notifyer::notifyBroadcast(channel, quitmsg);
    }
    this->removeClient(fd, index);
}

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
    if (cmdPack.size() == 0)
        return ;
    if (cmdPack[0] == "QUIT")
        this->parseQuit(client, command);
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