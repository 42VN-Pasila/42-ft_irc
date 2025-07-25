/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:32:41 by siuol             #+#    #+#             */
/*   Updated: 2025/07/25 11:13:26 by siuol            ###   ########.fr       */
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

        bool    isServerClient(const Client* client);
        bool    isServerChannel(const Channel* channel);
        bool    isServerChannelName(std::string& channelName);
        
        void    cmdJoin(Client* client, std::string& channelName);
        
    private :
        unsigned int        _port;
        std::string&        _password;
        std::set<Client*>   _clientList;
        std::set<Channel*>  _channelList;
};
