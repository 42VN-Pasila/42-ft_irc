/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:32:41 by siuol             #+#    #+#             */
/*   Updated: 2025/08/06 02:15:12 by htran-th         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

class Server
{
    public  :
        Server(unsigned int port, const std::string& password) : _server_fd(-2),
                                                                _port(port),
                                                                _password(password){};
        ~Server() {
            closeAllFds();
            std::cout << "Shutting down server!" << std::endl;
        };
        
        //Validation
        bool    isServerClient(Client* client);
        bool    isServerChannel(Channel* channel);
        bool    hasServerChannel(std::string& channelName);
        bool    hasServerClient(std::string& clientName);
        bool    validateChannel(Client* client, std::string& channelName);
        bool    validateOperator(Client* client, std::string& channelName);
        bool    validateTarget(Client* client, std::string& channelName, std::string& target);
        
        //cmdHandler
        void    handlerJoin(Client* client, std::string& channel, std::string& pass);
        void    handlerPrivmsg(Client* client, std::string& target, std::string& msg);
        void    handlerPart(Client* client, std::string& channel, std::string& msg);
        void    handlerInvite(Client* client, std::string& channel, std::string& targetUser);
        void    handlerKick(Client* client, std::string& channel, std::string& targetUser);
        void    handlerTopic(Client* client, std::string& channel, const std::string& topic = "");
        void    wrapperTopic(Client* client, std::string& channel, std::string& topic);
        void    handlerModeI(Client* client, std::string& channelName, bool mode);
        void    handlerModeT(Client* client, std::string& channelName, bool mode);
        void    handlerModeK(Client* client, std::string& channelName, const std::string& pass = "", bool mode);
        void    handlerModeO(Client* client, std::string& channelName, std::string& targetUser, bool mode);
        void    handlerModeL(Client* client, std::string& channelName, const unsigned int limit = 0, bool mode);
        
        
        //Utility
        bool    passwordRequired(Channel* channel, const std::string& pass = "");

        //Launch
        void    initSocket();
        void    bindAndListen();
        void    pollAndAccept();
        void    closeAllFds();

        //Main
        void    prs_cmd(Client* client, std::string& command);
        void    exec_cmd(Client* client, std::vector<std::string> cmds);
        
        
    private :
        int            _server_fd;
        std::vector<struct pollfd>          _poll_fds;
        std::map<int, Client*> _cl_nonverify; // Before input: NICK & USER
        unsigned int        _port;
        std::string        _password;
        std::map<std::string, Client*>   _clientList;
        std::map<std::string, Channel*>  _channelList;
        
        using Handler = void(Server::*)(Client* client, std::string& channelName, std::string& target);

        Handler _cmdExec[6] = 
        {
            &Server::handlerJoin,
            &Server::handlerPrivmsg,
            &Server::handlerPart,
            &Server::handlerKick,
            &Server::handlerInvite,
            &Server::wrapperTopic
        };
};

