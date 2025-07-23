/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:19:36 by caonguye          #+#    #+#             */
/*   Updated: 2025/07/23 17:18:55 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma oncce

#include "system.hpp"

class   Channel
{
    public  :
        Channel(std::string topic);
        ~Channel() = default;
        
    private :
        std::string     _topic;
        std::string     _operator;
        std::string     _password;
        std::string     _name;
        unsigned int    _limit;
        bool            _onlyInvite;
        
        //Getters
        const std::string   getTopic() const;
        const std::string   getOperator() const;
        const std::string   getPassword() const;
        const std::string   getName() const;
        const unsigned int  getLimit() const;
        const bool          getStatus() const;    
};