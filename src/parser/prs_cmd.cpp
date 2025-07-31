/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_cmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:47:44 by siuol             #+#    #+#             */
/*   Updated: 2025/07/31 20:44:56 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"


std::vector<std::string>    split(std::string cmd)
{
    std::istringstream          stream(cmd);
    std::vector<std::string>    command;
    std::string                 token;

    while (stream >> token)
        command.push_back(token);

    return command;
}

cmdType    prs_cmd(std::string command)
{
    if () 
}