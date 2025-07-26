/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_utility.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 03:06:19 by siuol             #+#    #+#             */
/*   Updated: 2025/07/26 03:31:42 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

bool    Server::passwordRequired(Channel* channel, const std::string& pass)
{
    if (channel->isRequiredPassword())
    {
        if (pass != channel->getPassword())
        {
            LOG_WARNING("[CHANNEL] : Incorrect password");
            return false;
        }
        return true;
    }
    return true;
}