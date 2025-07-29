/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_unsetter.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 01:02:43 by siuol             #+#    #+#             */
/*   Updated: 2025/07/29 14:24:59 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

int    Channel::unsetTopic()
{
    if (this->_topic.empty())
        return 483;
    this->_topic = "";
    return -1;
}

int    Channel::unsetPassword()
{
    if (this->_password.empty())
        return 484;
    this->_password = "";
    return -1;
}

int    Channel::unsetLimit()
{
    if (this->_limit == 0)
        return 459;
    this->_limit = 0;
    return -1;
}