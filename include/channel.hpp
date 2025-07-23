/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:19:36 by caonguye          #+#    #+#             */
/*   Updated: 2025/07/23 18:30:44 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

class   Client;
class   Channel
{
    public  :
        Channel(std::string topic);
        ~Channel() = default;
        
        //Getters
        const std::string       getTopic() const;
        const std::string       getOperator() const;
        const std::string       getPassword() const;
        const std::string       getName() const;
        const unsigned int      getLimit() const;
        const bool              getStatus() const;    
        
        //Setters
        void                    setTopic(const std::string& topic);
        void                    setOperator(const std::string& operatr);
        void                    setPassword(const std::string& password);
        void                    setChannelName(const std::string& name);
        void                    setLimit(const unsigned int& limit);
        void                    setInviteStatus(const bool& status);

        //Functional
        void                    addUser(const Client& target);
        void                    kickUser(const Client& target);
        void                    setOperators(const Client& target);
        
    private :
        std::string             _topic;
        std::string             _operator;
        std::string             _password;
        std::string             _channelName;
        unsigned int            _limit;
        bool                    _onlyInvite;
        
        std::set<std::string>   _members;
};