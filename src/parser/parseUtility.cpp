/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseUtility.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:58:04 by caonguye          #+#    #+#             */
/*   Updated: 2025/08/04 02:57:04 by siuol            ###   ########.fr       */
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
    
}