/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseGeneral.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:47:44 by siuol             #+#    #+#             */
/*   Updated: 2025/08/04 02:47:57 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

static std::string cmdType[]{"JOIN", "PRIVMSG", "PART", "KICK", "TOPIC", "MODE"};

void    Server::execCommand(Client* client, std::string cmd, std::string fullCommand)
{
    
}

void    Server::parseCommand(Client* client, std::string& command)
{
    if (command.empty())
    {
        Notifyer::notifyError(client, 485); 
        return ;
    }
    std::vector<std::string> cmdPack = parseSplit(command); 
    execCommand(client, cmdPack[0], command);
}