/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_functional.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 02:03:53 by siuol             #+#    #+#             */
/*   Updated: 2025/07/24 21:56:03 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    addUser(const Client* target)
{
    if (target == nullptr)
    {
        LOG_WARNING("[CHANNEL] : User cannot be null");
        std::cout << std::endl;
        return ;
    }
}

void    Channel::kickUser(const Client* target)
{
    if (target == nullptr)
    {
        LOG_WARNING("[CHANNEL] : User cannot be null");
        std::cout << std::endl;
        return ;
    }
    if (!this->isMember(target))
    {
        LOG_WARNING("[CHANNEL] : User is not in the channel");
        std::cout << std::endl;
        return ;
    }
    this->_members.erase(const_cast<Client*>(target));
    
}

void    Channel::removeOperator()
{
    if (this->_operator == nullptr)
    {
        LOG_WARNING("[CHANNEL] : Channel is not operated by any clients");
        return ;
    }
    this->_operator = nullptr;
}