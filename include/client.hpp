/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:40:45 by caonguye          #+#    #+#             */
/*   Updated: 2025/07/28 13:09:32 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

class Client
{
    public  :
        Client(std::string& userName, std::string& nickName,
                                    std::string& realName, int socket);
        ~Client() = default;

        //Getters
        const std::string   getUserName() const;
        const std::string   getNickName() const;
        const std::string   getRealName() const;
        const int           getSocket()   const;
        
        //Setters
        void    setUserName(const std::string& name);
        void    setNickName(const std::string& name);
        void    setRealName(const std::string& name);
        
    private :
        std::string     _userName;
        std::string     _nickName;
        std::string     _realName;
        int             _socket;
};