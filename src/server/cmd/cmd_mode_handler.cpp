/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode_handler.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:03:37 by caonguye          #+#    #+#             */
/*   Updated: 2025/07/26 17:40:53 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Server::handlerModeI(Client* client, std::string& channelName, bool mode)
{
    if (!this->hasServerChannel(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in the server");
        std::cout << std::endl;
        return ;
    }
}

void    Server::handlerModeT(Client* client, std::string& channelName, bool mode)
{
    if (!this->hasServerChannel(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in the server");
        std::cout << std::endl;
        return ;
    }
    
}

void    Server::handlerModeK(Client* client, std::string& channelName, const std::string& pass = "", bool mode)
{
    if (!this->hasServerChannel(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in the server");
        std::cout << std::endl;
        return ;
    }
    
}

void    Server::handlerModeO(Client* client, std::string& channelName, std::string& nickName, bool mode)
{
    if (!this->hasServerChannel(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in the server");
        std::cout << std::endl;
        return ;
    }
    
}

void    Server::handlerModeL(Client* client, std::string& channelName, const unsigned int limit = 0, bool mode)
{
    if (!this->hasServerChannel(channelName))
    {
        LOG_WARNING("[SERVER] : Channel is not in the server");
        std::cout << std::endl;
        return ;
    }
    
}
