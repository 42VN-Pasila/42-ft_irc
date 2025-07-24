/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_validation.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:21:55 by siuol             #+#    #+#             */
/*   Updated: 2025/07/24 21:56:09 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

bool    Channel::isOperator(const Client* target)
{
    if (target == nullptr)
    {
        LOG_WARNING("[CHANNEL] : User cannot be null");
        std::cout << std::endl;
        return ;
    }
    return (this->_operator == target);
}

bool    Channel::isMember(const Client* target)
{
    if (target == nullptr)
    {
        LOG_WARNING("[CHANNEL] : User cannot be null");
        std::cout << std::endl;
        return ;
    }
    return (this->_members.count(const_cast<Client*>(target)));
}

bool    Channel::isInviteOnly()
{
    return (this->_onlyInvite);
}

bool    Channel::isEmpty()
{
    return (this->_members.size() == 0);
}