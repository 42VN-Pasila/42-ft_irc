/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverUtility.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 03:06:19 by siuol             #+#    #+#             */
/*   Updated: 2025/09/03 22:33:26 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

bool    Server::passwordRequired(Channel* channel, const std::string& pass)
{
    if (channel->isRequiredPassword())
    {
        if (pass != channel->getPassword())
            return false;
        return true;
    }
    return true;
}

const   std::string Server::getPass() const
{
    return this->_password;
}

std::string getHost()
{
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    std::string host = hostname;
    return host;
}

std::string getDate()
{
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d %m %Y %H:%M:%S", timeinfo);
    std::string date = buffer;
    return date;
}