/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseUtility.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:58:04 by caonguye          #+#    #+#             */
/*   Updated: 2025/09/15 11:51:27 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

std::vector<std::string>    parseSplit(std::string& cmd)
{
    std::istringstream          stream(cmd);
    std::vector<std::string>    commandPack;
    std::string                 token;
    
    size_t pos = cmd.find(" :");
    if (pos != std::string::npos)
    {
        std::string commands = cmd.substr(0, pos);
        std::istringstream stream(commands);
        while (stream >> token)
            commandPack.push_back(token);
        std::string msg = cmd.substr(pos + 1);
        commandPack.push_back(msg); 
    }
    else
    {
        std::istringstream          stream(cmd);
        while (stream >> token)
            commandPack.push_back(token);
    }
    return commandPack;
}

std::vector<std::string>    parseSplitComma(std::string& cmd)
{
    std::vector<std::string>    result;
    std::istringstream          stream(cmd);
    std::string                 token;
    
    if (cmd[cmd.length() - 1] == ',')
        return {};
    while (std::getline(stream, token, ','))
    {
        if (token.empty())
            return {};
        else
            result.push_back(token);
    }
    return result;
}

bool    parseValidNumber(std::string& nbr)
{
    unsigned int value;

    auto    value_ptr = std::from_chars(nbr.data(), nbr.data() + nbr.length(), value);
    if (value_ptr.ec == std::errc::invalid_argument)
        return false;
    if (value_ptr.ec == std::errc::result_out_of_range)
        return false;
    if (value_ptr.ptr != nbr.data() + nbr.length())
        return false;
    return true;
}