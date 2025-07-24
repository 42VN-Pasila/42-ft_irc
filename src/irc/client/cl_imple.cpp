/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_imple.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:43:21 by siuol             #+#    #+#             */
/*   Updated: 2025/07/25 01:25:25 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

Client::Client(const std::string& userName, 
                const std::string& nickName) : _userName(userName),
                                               _nickName(nickName){};

const std::string   Client::getUserName() const
{
    return this->_userName;
}

const std::string   Client::getNickName() const
{
    return this->_nickName;
}

void    Client::setUserName(const std::string& userName)
{
    this->_userName = userName;
}

void    Client::setNickName(const std::string& nickName)
{
    this->_nickName = nickName;
}