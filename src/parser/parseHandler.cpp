/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:49:51 by siuol             #+#    #+#             */
/*   Updated: 2025/08/16 04:11:06 by siuol            ###   ########.fr       */
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
    for (size_t i = 0; i  < channelPack.size(); i++)
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
    if (size < 2)
    {
        Notifyer::notifyError(client, 495);
        return;
    }
    if (size < 3)
        topic = "";
    else
    {
        if (cmdPack[2][0] != ':' || cmdPack[2].length() == 1)
        {
            Notifyer::notifyError(client, 495);
            return;
        }
        for (size_t i = 2; i < size; i++)
            topic = (i == 2 ? cmdPack[i] : topic + " " + cmdPack[i]);
    }
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

void    Server::parseKick(Client* client, std::string& fullCommand)
{
    std::vector<std::string>    cmdPack;
    std::vector<std::string>    targetPack;
    std::string                 msg;
    int                         cmdSize;
    int                         targetSize;

    cmdPack = parseSplit(fullCommand);
    cmdSize = cmdPack.size();
    if (cmdSize < 3)
    {
        Notifyer::notifyError(client, 493);
        return;
    }
    targetPack = parseSplitComma(cmdPack[2]);
    targetSize = targetPack.size();
    if (cmdSize < 4)
        msg = "";
    else
    {
        if (cmdPack[3][0] != ':' || cmdPack[3].length() == 1)
        {
            Notifyer::notifyError(client, 495);
            return;
        }
        for (size_t i = 3; i < cmdSize; i++)
            msg = (i == 3 ? cmdPack[i] : msg + " " + cmdPack[i]);
    }
    for (size_t i = 0; i < targetSize; i++)
        this->handlerKick(client, cmdPack[1], targetPack[i], msg);
}

static std::string MultiTargetsPack[MULTI_TARGET_FUNCTIONS] = {"PART", "PRIVMSG"};

static std::function<void(Client* client)> MultiTargetsErrors[2] = 
{
    [](Client* client){Notifyer::notifyError(client, 491);},
    [](Client* client){Notifyer::notifyError(client, 492);}
};

void    Server::parseMultiTargets(Client* client, std::string& fullCommand)
{
    std::vector<std::string>    cmdPack;
    std::vector<std::string>    targetPack;
    std::string                 noti;
    int size;

    cmdPack = parseSplit(fullCommand);
    size = cmdPack.size();
    if (size < 2 || (size > 2 && (cmdPack[2][0] != ':' || cmdPack[2].length() == 1)))
    {
        for (int i = 0; i < MULTI_TARGET_FUNCTIONS; i++)
        {
            if (cmdPack[0] == MultiTargetsPack[i])
            {
                (MultiTargetsErrors[i])(client);
                return ;
            } 
        }
    }
    if (size < 3)
        noti = "";
    else
    {
        for (size_t i = 2; i < size; i++)
            noti = (i == 2 ? cmdPack[i] : noti + " " + cmdPack[i]);
    }

    targetPack = parseSplitComma(cmdPack[1]);

    for (int i = 0; i < MULTI_TARGET_FUNCTIONS; i++)
    {
        if (cmdPack[0] == MultiTargetsPack[i])
        {
            for (size_t j = 0; j < targetPack.size(); j++)
                (this->*_MultiTargetsFunctions[i])(client, targetPack[j], noti);
            return ;
        } 
    }
}
