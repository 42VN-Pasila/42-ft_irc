/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_unsetter.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 01:02:43 by siuol             #+#    #+#             */
/*   Updated: 2025/07/27 01:11:03 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Channel::unsetPassword()
{
    if (this->_password.empty())
    {
        LOG_WARNING("[CHANNEL] : This channel does not have password");
        std::cout << std::endl;
        return ;
    }
    this->_password = "";
}

void    Channel::unsetLimit()
{
    if (this->_limit == 0)
    {
        LOG_WARNING("[CHANNEL] : This channel does not have limit");
        std::cout << std::endl;
        return ;
    }
    this->_limit = 0;
}