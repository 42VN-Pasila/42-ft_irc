/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:40:45 by caonguye          #+#    #+#             */
/*   Updated: 2025/08/03 13:12:51 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

enum    status
{
    PASS,
    NICK,
    USER,
    COMPLETE 
};

class Client
{
    public  :
        Client(int socket);
        ~Client() = default;

        //Getters
        std::string   getUserName() const;
        std::string   getNickName() const;
        std::string   getRealName() const;
        int           getSocket()   const;
        status        getStatus()   const;
        
        //Setters
        void    setUserName(const std::string& name);
        void    setNickName(const std::string& name);
        void    setRealName(const std::string& name);
        void    setStatus(status newStatus);
        
    private :
        std::string     _userName;
        std::string     _nickName;
        std::string     _realName;
        int             _socket;
        status          _clientStatus;
};