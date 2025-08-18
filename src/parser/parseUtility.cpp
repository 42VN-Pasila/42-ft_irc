/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseUtility.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:58:04 by caonguye          #+#    #+#             */
/*   Updated: 2025/08/18 19:27:00 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

std::vector<std::string>    parseSplit(std::string& cmd)
{
    std::istringstream          stream(cmd);
    std::vector<std::string>    command;
    std::string                 token;

    while (stream >> token)
        command.push_back(token);
    return command;
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