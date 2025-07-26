/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_unsetter.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 01:02:43 by siuol             #+#    #+#             */
/*   Updated: 2025/07/27 01:04:08 by siuol            ###   ########.fr       */
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