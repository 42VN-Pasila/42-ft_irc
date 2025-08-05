/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifyer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:51:17 by siuol             #+#    #+#             */
/*   Updated: 2025/08/05 17:37:04 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

#define ERR_NOSUCHNICK          " :No such nickname in the server"     //401
#define ERR_NONICKNAMEGIVEN     " :No nickname given"                  //431
#define ERR_NOSUCHCHANNEL       " :No such channel in the server"      //403
#define ERR_ERRONEUSNICKNAME    " :Erroneous nickname"                 //432
#define ERR_NICKNAMEINUSE       " :Nickname is already in use"         //433
#define ERR_CANNOTSENDTOCHAN    " :Cannot send to channel"             //404
#define ERR_USERNOTONCHANNEL    " :User is not on that channel"        //442
#define ERR_USERONCHANNEL       " :User is already on channel"         //443
#define ERR_TARGNOTONSERVER     " :Receiver is not on that server"     //444
#define ERR_TARGNOTONCHANNEL    " :Receiver is not on that channel"    //445

#define ERR_SIGNINPASS          " :You must input password : PASS <password>"             //415
#define ERR_SIGNININVPASS       " :Invalid password"                     //416
#define ERR_SIGNINNICK          " :You must input nickname : NICK <nickname>"             //417
#define ERR_SIGNINUSER          " :You must input username and realname : USER <username> 0 * :<realname> " //418

#define ERR_CHANNELINCRPASSWORD " :Cannot join channel : Incorrect password"         //470
#define ERR_CHANNELISFULL       " :Cannot join channel : Channel is full"            //471
#define ERR_CHANNELINVITEONLY   " :Cannot join channel : Channel is in only invited mode" //473
#define ERR_CHANNELBADKEY       " :Cannot join channel (+k)"                         //475

#define ERR_NEEDMOREPARAMS      " :Not enough parameters"              //461
#define ERR_NOPRIVILEGES        " :Permission Denied- You're not an IRC operator"    //481
#define ERR_CHANOPRIVSNEEDED    " :User is not channel operator"        //482
#define ERR_UNKNOWNCOMMAND      " :Unknown command"                    //421

#define ERR_USERCANNOTBENULL    " :User cannot be null"                //446
#define ERR_USERNOTINVITED      " :User is not invited to channel"     //447
#define ERR_USERALRINVITED      " :User is already invited"            //448

#define ERR_CHANNELALROPR       " :Channel already has operator"       //451
#define ERR_CHANNELNOOPR        " :Channel has no operator"            //452
#define ERR_CHANNELNOTONLYINV   " :Channel not in invite-only mode"    //453
#define ERR_CHANNELALRINV       " :Channel already in invite-only mode" //454
#define ERR_CHANNELALRUNSETINV  " :Channel already unset invite-only mode" //455
#define ERR_CHANNELREACHLIM     " :Channel supports only 1000 users"   //456
#define ERR_CHANNELEMPTYTOPIC   " :Channel has no topic"               //457
#define ERR_CHANNELEMPTYPASS    " :Channel has no password"            //458
#define ERR_CHANNELZEROLIMIT    " :Channel has no limit"               //459

#define ERR_TOPICEMPTY          " :Topic cannot be empty"              //483
#define ERR_PASSWORDEMPTY       " :Password cannot be empty"           //484
#define ERR_EMPTYCMD            " :Command cannot be empty"            //485
#define ERR_WRONGCMD            " :Command not found"                  //486 

#define ERR_SYNTAXJOIN          " :Invalid JOIN syntax"                 //490
#define ERR_SYNTAXPART          " :Invalid PART syntax"                 //491
#define ERR_SYNTAXPRIVMSG       " :Invalid PRIVMSG syntax"              //492
#define ERR_SYNTAXKICK          " :Invalid KICK syntax"                 //493
#define ERR_SYNTAXINVITE        " :Invalid INVITE syntax"               //494
#define ERR_SYNTAXTOPIC         " :Invalid TOPIC syntax"                //495


class   Notifyer
{
    public  :
        static void notifySuccess(Client* client, const std::string& msg = "");
        
        static void notifyError(Client*  client, int code);
    
        static void notifyBroadcast(Channel* channel, const std::string& msg = "");

        static void sendMsg(Client* client, const std::string& msg = "");
        
    private :
        inline static std::map<int, std::string> _notifyCode = 
        {
            {401, ERR_NOSUCHNICK},
            {431, ERR_NONICKNAMEGIVEN},
            {432, ERR_ERRONEUSNICKNAME},
            {433, ERR_NICKNAMEINUSE},
            {403, ERR_NOSUCHCHANNEL},
            {404, ERR_CANNOTSENDTOCHAN},
            {446, ERR_USERCANNOTBENULL},
            {442, ERR_USERNOTONCHANNEL},
            {443, ERR_USERONCHANNEL},
            {447, ERR_USERNOTINVITED},
            {448, ERR_USERALRINVITED},
            {444, ERR_TARGNOTONSERVER},
            {445, ERR_TARGNOTONCHANNEL},
            {470, ERR_CHANNELINCRPASSWORD},
            {471, ERR_CHANNELISFULL},
            {473, ERR_CHANNELINVITEONLY},
            {475, ERR_CHANNELBADKEY},
            {451, ERR_CHANNELALROPR},
            {452, ERR_CHANNELNOOPR},
            {453, ERR_CHANNELNOTONLYINV},
            {454, ERR_CHANNELALRINV},
            {455, ERR_CHANNELALRUNSETINV},
            {456, ERR_CHANNELREACHLIM},
            {457, ERR_CHANNELEMPTYTOPIC},
            {458, ERR_CHANNELEMPTYPASS},
            {459, ERR_CHANNELZEROLIMIT},
            {482, ERR_CHANOPRIVSNEEDED},
            {481, ERR_NOPRIVILEGES},
            {461, ERR_NEEDMOREPARAMS},
            {421, ERR_UNKNOWNCOMMAND},
            {483, ERR_TOPICEMPTY},
            {484, ERR_PASSWORDEMPTY},
            {485, ERR_EMPTYCMD}
        };
};