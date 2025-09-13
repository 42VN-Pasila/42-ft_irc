/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:19:36 by caonguye          #+#    #+#             */
/*   Updated: 2025/09/13 14:31:16 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

class   Client;
class   Channel
{
    public  :
    Channel(const std::string& channelName) : _topic(""),
                                           _password(""),
                                           _channelName(channelName),
                                           _limit(0),
                                           _topicRight(false),
                                           _onlyInvite(false){};
        ~Channel() = default;
        
        //Getters
        const std::string&                      getTopic() const;
        const std::string&                      getPassword() const;
        const std::string&                      getChannelName() const;
        unsigned int                            getLimit() const;
        bool                                    getInviteStatus() const;    
        unsigned int                            getQuantity() const;
        const std::map<std::string, Client*>&   getMemberList() const;
        
        //Setters
        int                    setTopic(const std::string& topic);
        int                    setTopicRight(Client* client, std::string& channel);
        int                    setPassword(Client* client, const std::string& password, std::string& channel);
        int                    setOperator(Client* user, std::string& channel);
        int                    setLimit(Client* client, const unsigned int& limit, std::string& channel);
        int                    setInviteStatus(Client* user, const bool& status, std::string& channel);

        //Unsettes
        int                    unsetTopic();
        int                    unsetTopicRight(Client* client, std::string& channel);
        int                    unsetPassword(Client* client, std::string& channel);
        int                    unsetLimit(Client* client, std::string& channel);

        //Functional
        int                    addUser(Client* user, std::string& channel);
        int                    kickUser(Client* user, Client* target, std::string& channel);
        int                    inviteUser(Client* user, Client* target, std::string& channel);
        int                    removeUser(Client* user, std::string& channel);
        int                    removeOperator(Client* client, std::string& channel);
        
        //Validation
        int                     isOperator(Client* user);
        int                     isMember(Client* user);
        int                     isInvited(Client* user);
        bool                    isValidPassword(std::string pass);
        bool                    isTopicRight();
        bool                    isRequiredPassword();
        bool                    isInviteOnly();
        bool                    isEmpty();
        bool                    isAvailable();
         
        //Clean
        void                    cleanUp();

    private :
        std::string             _topic;
        std::string             _password;
        std::string             _channelName;
        unsigned int            _limit;
        bool                    _topicRight;
        bool                    _onlyInvite;
        
        std::map<std::string, Client*>       _members;
        std::map<std::string, Client*>       _invitation;
        std::map<std::string, Client*>       _operators;
};