/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseGeneral.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:47:44 by siuol             #+#    #+#             */
/*   Updated: 2025/09/03 22:37:54 by siuol            ###   ########.fr       */
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
    if (!client->getPasswordStatus() || !client->getNickStatus() || !client->getUserStatus())
    {
        this->removeClient(fd, index);
        return ;
    }

    if (cmdPack.size() < 2)
        msg = "";
    else
    {
        if (cmdPack[1][0] != ':' || cmdPack[1].length() == 1)
        {
            Notifyer::notifyError(client, 503);
            return ;
        }
        for (size_t i = 1; i < cmdPack.size(); i++)
            msg = (i == 1 ? cmdPack[i].substr(1) : msg + " " + cmdPack[i]);
    }
    
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
    else if (cmd == "PART" || cmd == "PRIVMSG")
        this->parseMultiTargets(client, fullCommand);
    else if (cmd == "KICK")
        this->parseKick(client, fullCommand);
    else if (cmd == "INVITE")
        this->parseInvite(client, fullCommand);
    else if (cmd == "TOPIC")
        this->parseTopic(client, fullCommand);
    else if (cmd == "MODE")
        this->parseMode(client, fullCommand);
    else if (cmd == "PING")
        this->parsePing(client, fullCommand);
    else
        Notifyer::notifyError(client, 421);
}

void    Server::parseCommand(Client* client, std::string& command, int& quitFlag)
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
    {
        this->parseQuit(client, command);
        quitFlag = 1;
        return ;
    }
    if (!client->getPasswordStatus() || !client->getNickStatus() || !client->getUserStatus())
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

void    Server::parsePreCommand(Client* client, std::string &fullcommand, int& quitFlag)
{
    std::stringstream ss(fullcommand);
    std::string command;

    while (std::getline(ss, command))
    {
        if (!command.empty() && command.back() == '\r')
            command.pop_back();
        std::cout <<"NOW PARSE" <<"--"<<command<<"--"<<std::endl;
        parseCommand(client, command, quitFlag);
    }
}