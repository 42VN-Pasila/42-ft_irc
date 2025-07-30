/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_utility.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 03:06:19 by siuol             #+#    #+#             */
/*   Updated: 2025/07/29 03:00:56 by siuol            ###   ########.fr       */
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