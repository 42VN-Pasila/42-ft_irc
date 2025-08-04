/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:49:51 by siuol             #+#    #+#             */
/*   Updated: 2025/08/04 03:20:17 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::parseJoin(Client* client, std::string fullCommand)
{
    std::vector<std::string>    cmdPack;
    std::vector<std::string>    channelPack;
    std::vector<std::string>    passwordPack;
    
    cmdPack = parseSplit(fullCommand);
    channelPack = parseSplitComma(cmdPack[1]);
    passwordPack = parseSplitComma(cmdPack[2]);
}