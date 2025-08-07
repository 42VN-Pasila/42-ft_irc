/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:32:41 by siuol             #+#    #+#             */
/*   Updated: 2025/08/07 11:13:33 by siuol            ###   ########.fr       */
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
        void    initSocket();
        void    bindAndListen();
        void    pollAndAccept();
        void    closeAllFds();
        
        //Exec
        void    parseCommand(Client* client, std::string& command);

    private :
        int                              _server_fd;
        unsigned int                     _port;
        std::vector<struct pollfd>	     _poll_fds;
        std::string                      _password;
        std::map<std::string, Client*>   _clientList;
        std::map<std::string, Channel*>  _channelList;
        std::map<int, Client*>           _socketList;
        
        using Handler = void(Server::*)(Client* client, std::string& channelName, std::string& target);

        Handler _MultiTargetsFunctions[3] = 
        {
            &Server::handlerPrivmsg,
            &Server::handlerPart,
            &Server::handlerKick,
        };

        //Validation
        bool    isServerClient(Client* client);
        bool    isServerChannel(Channel* channel);
        bool    hasServerChannel(std::string& channelName);
        bool    hasServerClient(std::string& clientName);
        bool    validateChannel(Client* client, std::string& channelName);
        bool    validateOperator(Client* client, std::string& channelName);
        bool    validateTarget(Client* client, std::string& target, std::string& channelName);
        
        //cmdHandler
        void    handlerJoin(Client* client, std::string& channel, std::string& pass);
        void    handlerPrivmsg(Client* client, std::string& target, std::string& msg);
        void    handlerPart(Client* client, std::string& channel, std::string& msg);
        void    handlerInvite(Client* client, std::string& channel, std::string& targetUser);
        void    handlerKick(Client* client, std::string& channel, std::string& targetUser);
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

        
        //Parse
        void    parseSign(Client* client, std::string& cmd);
        void    parseQuit(Client* client, std::string& cmd);
        void    parseSignPASS(Client* client, std::vector<std::string> command);
        void    parseSignNICK(Client* client, std::vector<std::string> command);
        void    parseSignUSER(Client* client, std::vector<std::string> command);
        void    execCommand(Client* client, std::string cmd, std::string fullCommand);

        //ParseCmd
        void    parseJoin(Client* client, std::string& fullCommand);
        void    parseTopic(Client* client, std::string& fullCommand);
        void    parseInvite(Client* client, std::string& fullCommand);
        void    parseMultiTargets(Client* client, std::string& fullCommand);
        
        //ParseMode
        void    parseMode(Client* client, std::string& fullCommand);
        void    parseModeI(Client* client, std::string& fullCommand);
        void    parseModeK(Client* client, std::string& fullCommand);
        void    parseModeT(Client* client, std::string& fullCommand);
        void    parseModeL(Client* client, std::string& fullCommand);
        void    parseModeO(Client* client, std::string& fullCommand);

        using Mode  = void(Server::*)(Client* client, std::string& fullCommand);

        Mode    _parseModePack[5] = 
        {
            &Server::parseModeI,
            &Server::parseModeK,
            &Server::parseModeT,
            &Server::parseModeL,
            &Server::parseModeO
        };
};

