/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:49:51 by siuol             #+#    #+#             */
/*   Updated: 2025/08/05 18:50:48 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::parseJoin(Client* client, std::string fullCommand)
{
    std::vector<std::string>    cmdPack;
    std::vector<std::string>    channelPack;
    std::vector<std::string>    passwordPack;
    
    cmdPack = parseSplit(fullCommand);
    if (cmdPack.size() > 3 || cmdPack.size() < 2)
    {
        Notifyer::notifyError(client, 490);
        return;
    }
    channelPack = parseSplitComma(cmdPack[1]);
    
    if (cmdPack.size() > 2)
        passwordPack = parseSplitComma(cmdPack[2]);
    for (int i = 0; i  < channelPack.size(); i++)
    {
        std::string password = (i < passwordPack.size() ? passwordPack[i] : "");
        this->handlerJoin(client, channelPack[i], password);
    }
}

void    Server::parseMultiTargets(Client* client, std::string fullCommand)
{
    
}

std::string MultiTargetsPack[MULTI_TARGET_FUNCTIONS] = {"PART", "PRIVMSG", "KICK"};

void    Server::parseMultiTargets(Client* client, std::string fullCommand)
{
    std::vector<std::string>    cmdPack;
    std::vector<std::string>    targetPack;
    std::string                 noti;
    int size;

    cmdPack = parseSplit(fullCommand);
    size = cmdPack.size();
    if (size > 3 || size < 2)
    {
        if (cmdPack[0] == "PART")
            Notifyer::notifyError(client, 491);
        else if (cmdPack[0] == "PRIVMSG")
            Notifyer::notifyError(client, 492);
        else if (cmdPack[0] == "KICK")
            Notifyer::notifyError(client, 493);
        return;
    }
    targetPack = parseSplitComma(cmdPack[1]);

    noti = (size > 2 ? cmdPack[2].substr(1) : "");
    for (int i = 0; i < MULTI_TARGET_FUNCTIONS; i++)
    {
        if (cmdPack[0] == MultiTargetsPack[i])
        {
            for (int j = 0; j < size; j++)
                (this->*_MultiTargetsFunctions[i])(client, targetPack[j], noti);
            return ;
        } 
    }
}
