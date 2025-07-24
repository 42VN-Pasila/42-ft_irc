/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:19:36 by caonguye          #+#    #+#             */
/*   Updated: 2025/07/24 11:36:31 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

class   Client;
class   Channel
{
    public  :
    Channel(const std::string& channelName) : _topic(""),
                                           _operator(nullptr),
                                           _password(""),
                                           _channelName(channelName),
                                           _limit(0),
                                           _onlyInvite(false){};
        ~Channel() = default;
        
        //Getters
        const std::string&      getTopic() const;
        const Client*           getOperator() const;
        const std::string&      getPassword() const;
        const std::string&      getChannelName() const;
        const unsigned int      getLimit() const;
        const bool              getInviteStatus() const;    
        const unsigned int      getQuantity() const;
        
        //Setters
        void                    setTopic(const std::string& topic);
        void                    setPassword(const std::string& password);
        void                    setOperator(const Client* target);
        void                    setLimit(const unsigned int& limit);
        void                    setInviteStatus(const bool& status);

        //Functional
        void                    addUser(const Client* target);
        void                    kickUser(const Client* target);
        void                    removeOperator();
        
        //Validation
        bool                    isOperator(const Client* target);
        bool                    isMember(const Client* target);
        bool                    isInviteOnly();
        bool                    isEmpty();
        
    private :
        std::string             _topic;
        Client*                 _operator;
        std::string             _password;
        std::string             _channelName;
        unsigned int            _limit;
        bool                    _onlyInvite;
        
        std::set<Client*>       _members;
        std::set<Client*>       _invitation;
};