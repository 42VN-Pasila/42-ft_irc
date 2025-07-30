/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:19:36 by caonguye          #+#    #+#             */
/*   Updated: 2025/07/30 22:05:48 by siuol            ###   ########.fr       */
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
                                           _topicRight(false),
                                           _onlyInvite(false){};
        ~Channel() = default;
        
        //Getters
        const std::string&                      getTopic() const;
        const Client*                           getOperator() const;
        const std::string&                      getPassword() const;
        const std::string&                      getChannelName() const;
        const unsigned int                      getLimit() const;
        const bool                              getInviteStatus() const;    
        const unsigned int                      getQuantity() const;
        const std::map<std::string, Client*>    getMemberList() const;
        
        //Setters
        int                    setTopic(const std::string& topic);
        int                    setTopicRight();
        int                    setPassword(const std::string& password);
        int                    setOperator(Client* user);
        int                    setLimit(const unsigned int& limit);
        int                    setInviteStatus(const bool& status);

        //Unsettes
        int                    unsetTopic();
        int                    unsetTopicRight();
        int                    unsetPassword();
        int                    unsetLimit();
        int                    unsetOperator(Client* client1);

        //Functional
        int                    addUser(Client* user);
        int                    kickUser(Client* user);
        int                    inviteUser(Client* user);
        int                    removeUser(Client* user);
        int                    removeOperator();
        
        //Validation
        int                     isOperator(Client* user);
        int                     isMember(Client* user);
        int                     isInvited(Client* user);
        bool                    isRequiredPassword();
        bool                    isInviteOnly();
        bool                    isEmpty();
        bool                    isAvailable();
         
        
    private :
        std::string             _topic;
        Client*                 _operator;
        std::string             _password;
        std::string             _channelName;
        unsigned int            _limit;
        bool                    _topicRight;
        bool                    _onlyInvite;
        
        std::map<std::string, Client*>       _members;
        std::map<std::string, Client*>       _invitation;
};