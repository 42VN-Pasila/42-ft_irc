/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverUtility.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 03:06:19 by siuol             #+#    #+#             */
<<<<<<< HEAD:src/server/implementation/sv_utility.cpp
/*   Updated: 2025/08/02 19:18:35 by tripham          ###   ########.fr       */
=======
/*   Updated: 2025/09/03 22:39:32 by siuol            ###   ########.fr       */
>>>>>>> main:src/server/implementation/serverUtility.cpp
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

<<<<<<< HEAD:src/server/implementation/sv_utility.cpp
unsigned int Server::getPort() const {
	return this->_port;
}

void Server::setPort (unsigned int port) {
	this->_port = port;
}
=======
const   std::string Server::getPass() const
{
    return this->_password;
}
>>>>>>> main:src/server/implementation/serverUtility.cpp
