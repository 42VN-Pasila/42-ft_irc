/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverUtility.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 03:06:19 by siuol             #+#    #+#             */
/*   Updated: 2025/09/03 22:39:32 by siuol            ###   ########.fr       */
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
