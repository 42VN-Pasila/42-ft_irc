/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_functional.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 02:03:53 by siuol             #+#    #+#             */
/*   Updated: 2025/07/24 22:11:55 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void    Channel::addUser(const Client* target)
{
    if (target == nullptr)
    {
        LOG_WARNING("[CHANNEL] : User cannot be null");
        std::cout << std::endl;
        return ;
    }
    if (this->isMember(target))
    {
        LOG_WARNING("[CHANNEL] : User is already in the channel");
        std::cout << std::endl;
        return;
    }
    
    this->_members.insert(const_cast<Client*>(target));
    LOG_SUCCESS("[CHANNEL] : ");
    std::cout << target->getName();
    LOG_SUCCESS(" is added to the channel");
    std::cout << std::endl;
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
        LOG_SUCCESS("[CHANNEL] : ");
    std::cout << target->getName();
    LOG_SUCCESS(" is removed out of the channel");
    std::cout << std::endl;
}

void    Channel::removeOperator()
{
    if (this->_operator == nullptr)
    {
        LOG_WARNING("[CHANNEL] : Channel is not operated by any clients");
        std::cout << std::endl;
        return ;
    }
    this->_operator = nullptr;
    LOG_SUCCESS("[CHANNEL] : Channel now has no operator");
    std::cout << std::endl;
}