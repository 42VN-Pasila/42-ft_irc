/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:32:41 by siuol             #+#    #+#             */
/*   Updated: 2025/07/28 01:01:17 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

class Server
{
    public  :
        Server(unsigned int port, const std::string& password) : _port(port),
                                                        _password(password){};
        ~Server() = default;
        
        //Validation
        bool    isServerClient(Client* client);
        bool    isServerChannel(Channel* channel);
        bool    hasServerChannel(std::string& channelName);
        bool    hasServerClient(std::string& clientName);
        
        //cmdHandler
        void    handlerJoin(Client* client, std::string& channelName, std::string& pass);
        void    handlerPrivmsg(Client* client, std::string& target, std::string& msg);
        void    handlerPart(Client* client, std::string& channelName, std::string& msg);
        void    handlerInvite(Client* client, std::string& channelName, std::string& nickname);
        void    handlerKick(Client* client, std::string& channelName, std::string& targetUser);
        void    handlerTopic(Client* client, std::string& channelName, std::string& topic);
        void    handlerModeI(Client* client, std::string& channelName, bool mode);
        void    handlerModeT(Client* client, std::string& channelName, bool mode);
        void    handlerModeK(Client* client, std::string& channelName, const std::string& pass = "", bool mode);
        void    handlerModeO(Client* client, std::string& channelName, std::string& nickName, bool mode);
        void    handlerModeL(Client* client, std::string& channelName, const unsigned int limit = 0, bool mode);
        
        //Utility
        bool    passwordRequired(Channel* channel, const std::string& pass = "");
        
    private :
        unsigned int        _port;
        std::string        _password;
        std::map<std::string, Client*>   _clientList;
        std::map<std::string, Channel*>  _channelList;
};
