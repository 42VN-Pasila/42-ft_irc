/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implementation.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:43:21 by siuol             #+#    #+#             */
/*   Updated: 2025/09/02 23:50:38 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

Client::Client(int socket) : _userName(""),
                                                    _nickName(""),
                                                    _realName(""),
                                                    _socket(socket),
                                                    _passwordStatus(false),
                                                    _nickStatus(false),
                                                    _userStatus(false){};

std::string   Client::getUserName() const
{
    return this->_userName;
}

std::string   Client::getNickName() const
{
    return this->_nickName;
}

std::string   Client::getRealName() const
{
    return this->_realName;
}

int   Client::getSocket() const
{
    return this->_socket;
}

bool    Client::getPasswordStatus() const
{
    return this->_passwordStatus;
}

bool    Client::getNickStatus() const
{
    return this->_nickStatus;
}

bool    Client::getUserStatus() const
{
    return this->_userStatus;
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

void    Client::setPasswordStatus(bool status)
{
    this->_passwordStatus = status;
}

void    Client::setNickStatus(bool status)
{
    this->_nickStatus = status;
}

void    Client::setUserStatus(bool status)
{
    this->_userStatus = status;
}