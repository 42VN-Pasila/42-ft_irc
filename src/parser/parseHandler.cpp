/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:49:51 by siuol             #+#    #+#             */
/*   Updated: 2025/08/06 02:02:36 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::parseJoin(Client* client, std::string& fullCommand)
{
    std::vector<std::string>    cmdPack;
    std::vector<std::string>    channelPack;
    std::vector<std::string>    passwordPack;
    int                         size;
    
    cmdPack = parseSplit(fullCommand);
    size = cmdPack.size();
    if (size > 3 || size < 2)
    {
        Notifyer::notifyError(client, 490);
        return;
    }
    channelPack = parseSplitComma(cmdPack[1]);
    
    if (size > 2)
        passwordPack = parseSplitComma(cmdPack[2]);
    for (int i = 0; i  < channelPack.size(); i++)
    {
        std::string password = (i < passwordPack.size() ? passwordPack[i] : "");
        this->handlerJoin(client, channelPack[i], password);
    }
}

void    Server::parseTopic(Client* client, std::string& fullCommand)
{
    std::vector<std::string>    cmdPack;
    std::string                 topic;
    int                         size;
    
    cmdPack = parseSplit(fullCommand);
    size = cmdPack.size();
    if (size > 3 || size < 2)
    {
        Notifyer::notifyError(client, 495);
        return;
    }
    topic = (size < 3 ? "" : cmdPack[2].substr(1));
    this->handlerTopic(client, cmdPack[1], topic);
}

void    Server::parseInvite(Client* client, std::string& fullCommand)
{
    std::vector<std::string>    cmdPack;
    int                         size;
    
    cmdPack = parseSplit(fullCommand);
    size = cmdPack.size();
    if (size != 3)
    {
        Notifyer::notifyError(client, 494);
        return;
    }
    this->handlerInvite(client, cmdPack[1], cmdPack[2]);
}

static std::string MultiTargetsPack[MULTI_TARGET_FUNCTIONS] = {"PART", "PRIVMSG", "KICK"};

void    Server::parseMultiTargets(Client* client, std::string& fullCommand)
{
    std::vector<std::string>    cmdPack;
    std::vector<std::string>    targetPack;
    std::string                 noti;
    int size;

    cmdPack = parseSplit(fullCommand);
    size = cmdPack.size();
    if (size > 3 || size < 2)
    {
        for (int i = 0; i < MULTI_TARGET_FUNCTIONS; i++)
        {
            if (cmdPack[0] == MultiTargetsPack[i])
            {
                (this->_MultiTargetsErrors[i])(client);
                return ;
            } 
        }
    }
    targetPack = parseSplitComma(cmdPack[1]);

    noti = (size > 2 ? cmdPack[2].substr(1) : "");
    for (int i = 0; i < MULTI_TARGET_FUNCTIONS; i++)
    {
        if (cmdPack[0] == MultiTargetsPack[i])
        {
            for (int j = 0; j < targetPack.size(); j++)
                (this->*_MultiTargetsFunctions[i])(client, targetPack[j], noti);
            return ;
        } 
    }
}
