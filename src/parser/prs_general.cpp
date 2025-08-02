/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_general.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:47:44 by siuol             #+#    #+#             */
/*   Updated: 2025/08/02 05:06:44 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"


static std::vector<std::string>    split(std::string& cmd)
{
    std::istringstream          stream(cmd);
    std::vector<std::string>    command;
    std::string                 token;

    while (stream >> token)
        command.push_back(token);
    return command;
}

static std::string cmdType[]{"JOIN", "PRIVMSG", "PART", "KICK", "TOPIC", "MODE"};

static  void    exec_cmd(Client* client, std::vector<std::string> cmds)
{
    
}

void    Server::prs_cmd(Client* client, std::string& command)
{
    if (command.empty())
    {
        Notifyer::notifyError(client, 485); 
        return ;
    }
    std::vector<std::string> cmdPack = split(command); 
    exec_cmd(client, cmdPack);
}