/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:49:51 by siuol             #+#    #+#             */
/*   Updated: 2025/08/05 01:06:55 by siuol            ###   ########.fr       */
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
        Notifyer::notifyError(client, );
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

void    Server::parseSingleTargets(Client* client, std::string fullCommand)
{
    
}

void    Server::parseMultiTargets(Client* client, std::string fullCommand)
{
    
}