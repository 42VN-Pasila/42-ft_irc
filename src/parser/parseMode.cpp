/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseMode.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:48:03 by siuol             #+#    #+#             */
/*   Updated: 2025/09/16 14:24:12 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::parseModeI(Client* client, std::string& fullCommand)
{
    std::vector<std::string>    cmdPack;
    bool                        mode;
    int                         size;

    cmdPack = parseSplit(fullCommand);
    size = cmdPack.size();
    if (size != 3 || (cmdPack[2][0] != '+' && cmdPack[2][0] != '-'))
    {
        Notifyer::notifyError(client, 497);
        return ;
    }
    mode = (cmdPack[2][0] == '+' ? on : off);
    this->handlerModeI(client, cmdPack[1], mode);
}

void    Server::parseModeK(Client* client, std::string& fullCommand)
{
    std::vector<std::string>    cmdPack;
    std::string                 password;
    bool                        mode;
    int                         size;

    cmdPack = parseSplit(fullCommand);
    size = cmdPack.size();
    if  ((cmdPack[2][0] == '+' && size != 4) || (cmdPack[2][0] == '-' && size != 3))
    {
        Notifyer::notifyError(client, 498);
        return ;
    }
    mode = (cmdPack[2][0] == '+' ? on : off);
    password = (mode == on ? cmdPack[3] : "");
    this->handlerModeK(client, cmdPack[1], password, mode);
}

void    Server::parseModeT(Client* client, std::string& fullCommand)
{
    std::vector<std::string>    cmdPack;
    bool                        mode;
    int                         size;

    cmdPack = parseSplit(fullCommand);
    size = cmdPack.size();
    if (size != 3 || (cmdPack[2][0] != '+' && cmdPack[2][0] != '-'))
    {
        Notifyer::notifyError(client, 501);
        return ;
    }
    mode = (cmdPack[2][0] == '+' ? on : off);
    this->handlerModeT(client, cmdPack[1], mode);
}

void    Server::parseModeL(Client* client, std::string& fullCommand)
{
    std::vector<std::string>    cmdPack;
    bool                        mode;
    int                         size;
    unsigned int                limit = 0;                     

    cmdPack = parseSplit(fullCommand);
    size = cmdPack.size();
    if  ((cmdPack[2][0] == '+' && size != 4) || (cmdPack[2][0] == '-' && size != 3))
    {
        Notifyer::notifyError(client, 499);
        return ;
    }
    mode = (cmdPack[2][0] == '+' ? on : off);
    if (mode == on)
    {
        if (!parseValidNumber(cmdPack[3]))
        {
            Notifyer::notifyError(client, 499);
            return ;         
        }
        limit = std::stoi(cmdPack[3]);
    }
    this->handlerModeL(client, cmdPack[1], limit, mode);
}

void    Server::parseModeO(Client* client, std::string& fullCommand)
{
    std::vector<std::string>    cmdPack;
    bool                        mode;
    int                         size;

    cmdPack = parseSplit(fullCommand);
    size = cmdPack.size();
    if (size != 4 || (cmdPack[2][0] != '+' && cmdPack[2][0] != '-'))
    {
        Notifyer::notifyError(client, 500);
        return ;
    }
    mode = (cmdPack[2][0] == '+' ? on : off);
    this->handlerModeO(client, cmdPack[1], cmdPack[3], mode);
}

static std::string modePack[] = {"i", "k", "t", "l", "o"};

void    Server::parseMode(Client* client, std::string& fullCommand)
{
    std::vector<std::string>    cmdPack;
    std::string                 typeMode;
    int                         size;
    
    cmdPack = parseSplit(fullCommand);
    size = cmdPack.size();
    if (size < 3 || size > 4 || cmdPack[2].length() < 2)
    {
        Notifyer::notifyError(client, 496);
        return ;
    }
    typeMode = cmdPack[2][1];
    for (int i = 0; i < MODE_QTT; i++)
    {
        if (typeMode == modePack[i])
        {
            (this->*_parseModePack[i])(client, fullCommand);
            return ;
        }
    }
    Notifyer::notifyError(client, 496);
}