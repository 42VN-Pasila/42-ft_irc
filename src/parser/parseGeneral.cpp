/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_general.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:47:44 by siuol             #+#    #+#             */
/*   Updated: 2025/08/02 17:58:30 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

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