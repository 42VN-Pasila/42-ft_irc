/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifyer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:51:17 by siuol             #+#    #+#             */
/*   Updated: 2025/07/28 10:17:05 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

#define ERR_NOSUCHNICK          " :No such nick/channel"
#define ERR_NONICKNAMEGIVEN     " :No nickname given"  
#define ERR_ERRONEUSNICKNAME    " :Erroneous nickname"
#define ERR_NICKNAMEINUSE       " :Nickname is already in use"
#define ERR_NOSUCHCHANNEL       " :No such channel"
#define ERR_CANNOTSENDTOCHAN    " :Cannot send to channel"
#define ERR_NOTONCHANNEL        " :You're not on that channel" 
#define ERR_USERONCHANNEL       " :is already on channel"
#define ERR_CHANNELISFULL       " :Cannot join channel (+l)"
#define ERR_INVITEONLYCHAN      " :Cannot join channel (+i)"
#define ERR_BADCHANNELKEY       " :Cannot join channel (+k)"
#define ERR_CHANOPRIVSNEEDED    " :You're not channel operator"
#define ERR_NOPRIVILEGES        " :Permission Denied- You're not an IRC operator"
#define ERR_NEEDMOREPARAMS      " :Not enough parameters"
#define ERR_UNKNOWNCOMMAND      " :Unknown command"
#define RPL_TOPIC               " :"  
#define RPL_INVITING            " " 

class   Notifyer
{
    public  :
        
    private :
        inline static const std::map<int, std::string> Notifyer::_notifyCode = 
        {
            {401, ERR_NOSUCHNICK},
            {431, ERR_NONICKNAMEGIVEN},
            {432, ERR_ERRONEUSNICKNAME},
            {433, ERR_NICKNAMEINUSE},
            {403, ERR_NOSUCHCHANNEL},
            {404, ERR_CANNOTSENDTOCHAN},
            {442, ERR_NOTONCHANNEL},
            {443, ERR_USERONCHANNEL},
            {471, ERR_CHANNELISFULL},
            {473, ERR_INVITEONLYCHAN},
            {475, ERR_BADCHANNELKEY},
            {482, ERR_CHANOPRIVSNEEDED},
            {481, ERR_NOPRIVILEGES},
            {461, ERR_NEEDMOREPARAMS},
            {421, ERR_UNKNOWNCOMMAND},
            {332, RPL_TOPIC}, 
            {341, RPL_INVITING}
        };
};