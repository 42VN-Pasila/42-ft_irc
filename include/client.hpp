/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:40:45 by caonguye          #+#    #+#             */
/*   Updated: 2025/09/02 23:49:34 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

class Client
{
    public  :
        Client(int socket);
        ~Client() = default;

        //Getters
        std::string   getUserName()         const;
        std::string   getNickName()         const;
        std::string   getRealName()         const;
        int           getSocket()           const;
        bool          getPasswordStatus()   const;
        bool          getNickStatus()       const;
        bool          getUserStatus()       const;
        
        //Setters
        void    setUserName(const std::string& name);
        void    setNickName(const std::string& name);
        void    setRealName(const std::string& name);
        void    setPasswordStatus(bool status);
        void    setNickStatus(bool status);
        void    setUserStatus(bool status);
        
    private :
        std::string     _userName;
        std::string     _nickName;
        std::string     _realName;
        int             _socket;
        bool            _passwordStatus;
        bool            _nickStatus;
        bool            _userStatus;
};