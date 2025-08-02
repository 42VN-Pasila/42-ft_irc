/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_general.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:47:44 by siuol             #+#    #+#             */
/*   Updated: 2025/08/02 05:31:54 by siuol            ###   ########.fr       */
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

void    Server::exec_cmd(Client* client, std::vector<std::string> cmds)
{
    for (int i = 0; i < 5; i++)
    {
        if (cmds[0] == cmdType[i])
        {
            (this->*_cmdExec[i])(client, cmds[1], cmds[2]);
            return ;
        }
    }
    if (cmds[0] == cmdType[5])
    {
        this->exec_mode(client, cmds);
        return;
    }
    else
    {
        Notifyer::notifyError(client, 486); 
        return ;
    }
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