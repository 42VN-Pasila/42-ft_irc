/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:32:41 by siuol             #+#    #+#             */
/*   Updated: 2025/09/13 15:55:59 by tripham          ###   ########.fr       */
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
        ~Server();
        
        //Launch
        void            initSocket();
        void            bindAndListen();
        void            pollAndAccept();
        void            gracefullyShutDown();
        void            removeClient(int client_fd, int index);
        void            closeAllFds();
        int             getIndex(int fd) const;
        
        //Exec
        void    parsePreCommand(Client* client, std::string& fullcommand, int& quitFlag);
        void    parseCommand(Client* client, std::string& command, int& quitFlag);

    private :
        int                              _server_fd;
        unsigned int                     _port;
        std::vector<struct pollfd>	     _poll_fds;
        std::string                      _password;
        std::map<std::string, Client*>   _clientList;
        std::map<std::string, Channel*>  _channelList;
        std::map<int, Client*>           _socketList;
        
        using Handler = void(Server::*)(Client* client, std::string& channelName, std::string& target);

        Handler _MultiTargetsFunctions[2] = 
        {
            &Server::handlerPart,
            &Server::handlerPrivmsg
        };

        //Validation
        bool    isServerClient(Client* client);
        bool    isServerChannel(Channel* channel);
        bool    hasServerChannel(std::string& channelName);
        bool    hasServerClient(std::string& clientName);
        void    validateRegistration(Client* client, std::string& nickname);
        bool    validateChannel(Client* client, std::string& channelName);
        bool    validateOperator(Client* client, std::string& channelName);
        bool    validateTargetIn(Client* client, std::string& target, std::string& channelName);
        bool    validateTargetOut(Client* client, std::string& target, std::string& channelName);
        
        //cmdHandler
        void    handlerJoin(Client* client, std::string& channel, std::string& pass);
        void    handlerPrivmsg(Client* client, std::string& target, std::string& msg);
        void    handlerPart(Client* client, std::string& channel, std::string& msg);
        void    handlerInvite(Client* client, std::string& channel, std::string& targetUser);
        void    handlerKick(Client* client, std::string& channel, std::string& targetUser, std::string& msg);
        void    handlerTopic(Client* client, std::string& channel, std::string& topic);
        void    handlerModeI(Client* client, std::string& channelName, bool = false);
        void    handlerModeT(Client* client, std::string& channelName, bool = false);
        void    handlerModeK(Client* client, std::string& channelName, const std::string& pass = "", bool mode = false);
        void    handlerModeO(Client* client, std::string& channelName, std::string& targetUser, bool mode  = false);
        void    handlerModeL(Client* client, std::string& channelName, const unsigned int limit = 0, bool = false);
        
        //Getter
        const std::string getPass() const;
        
        //Utility
        bool    passwordRequired(Channel* channel, const std::string& pass = "");

        //Main
        void    prs_cmd(Client* client, std::string& command);
        void    exec_cmd(Client* client, std::vector<std::string> cmds);
        
        
    private :
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

