/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_imple.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:43:21 by siuol             #+#    #+#             */
/*   Updated: 2025/08/03 13:12:37 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

Client::Client(int socket) : _userName(""),
                                                    _nickName(""),
                                                    _realName(""),
                                                    _socket(socket),
                                                    _clientStatus(PASS){};

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

status    Client::getStatus() const
{
    return this->_clientStatus;
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

void    Client::setStatus(status newStatus)
{
    this->_clientStatus = newStatus;
}