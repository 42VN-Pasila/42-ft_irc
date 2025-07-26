/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:32:41 by siuol             #+#    #+#             */
/*   Updated: 2025/07/26 03:06:01 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

class Server
{
    public  :
        Server(unsigned int port, std::string& password) : _port(port),
                                                        _password(password){};
        ~Server() = default;
        
        //Validation
        bool    isServerClient(const Client* client);
        bool    isServerChannel(const Channel* channel);
        bool    hasServerChannel(std::string& channelName);
        
        //cmdHandler
        void    cmdJoin(Client* client, std::string& channelName);
        
        //Utility
        void    passwordRequired(Channel* channel);
        
    private :
        unsigned int        _port;
        std::string&        _password;
        std::map<std::string, Client*>   _clientList;
        std::map<std::string, Channel*>  _channelList;
};
