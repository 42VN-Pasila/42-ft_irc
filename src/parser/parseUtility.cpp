/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseUtility.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:58:04 by caonguye          #+#    #+#             */
/*   Updated: 2025/08/06 01:19:42 by siuol            ###   ########.fr       */
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
    
    while (std::getline(stream, token, ','))
        result.push_back(token);
    return result;
}
