/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_imple.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:43:21 by siuol             #+#    #+#             */
/*   Updated: 2025/07/28 13:14:56 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

Client::Client(std::string& userName, 
                std::string& nickName,
                std::string& realName, int socket) : _userName(userName),
                                                    _nickName(nickName),
                                                    _realName(realName),
                                                    _socket(socket){};

const std::string   Client::getUserName() const
{
    return this->_userName;
}

const std::string   Client::getNickName() const
{
    return this->_nickName;
}

const std::string   Client::getRealName() const
{
    return this->_realName;
}

const int   Client::getSocket() const
{
    return this->_socket;
}

void    Client::setUserName(const std::string& userName)
{
    this->_userName = userName;
}

void    Client::setNickName(const std::string& nickName)
{
    this->_nickName = nickName;
}

void    Client::setRealName(const std::string& realName)
{
    this->_realName = realName;
}
