/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:40:45 by caonguye          #+#    #+#             */
/*   Updated: 2025/07/26 04:08:41 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

class Client
{
    public  :
        Client(const std::string& userName, const std::string& nickName,
                                            const std::string& realName);
        ~Client() = default;

        //Getters
        const std::string   getUserName() const;
        const std::string   getNickName() const;
        const std::string   getRealName() const;
        
        //Setters
        void    setUserName(const std::string& name);
        void    setNickName(const std::string& name);
        void    setRealName(const std::string& name);
        
    private :
        std::string _userName;
        std::string _nickName;
        std::string _realName;
};