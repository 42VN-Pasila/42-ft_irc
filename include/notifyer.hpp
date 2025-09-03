/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifyer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:51:17 by siuol             #+#    #+#             */
/*   Updated: 2025/09/03 09:25:58 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

#define ERR_ALREADYPASS         " :Password is already inputted"       //390
#define ERR_ALREADYNICK         " :Nickname is already inputtted"      //391
#define ERR_ALREADYUSER         " :User is already inputted"           //392
#define ERR_NOPASS              " :Password has not been inputted"       //393
#define ERR_NONICK              " :Nickname has not been inputted"      //394
#define ERR_NOUSER              " :User has not been inputted"           //395

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
#define ERR_TARGETONCHANNEL     " :Receiver is already in the channel" //441

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
#define ERR_CANNOTKICKUS        " :You cannot kick yourself"           //460

#define ERR_TOPICEMPTY          " :Topic cannot be empty"              //483
#define ERR_PASSWORDEMPTY       " :Password cannot be empty"           //484
#define ERR_EMPTYCMD            " :Command cannot be empty"            //485
#define ERR_WRONGCMD            " :Command not found"                  //486
#define ERR_INVALIDPASSWORD     " :Password contains special character \"\\n\\t\\r' ',:#+-\"" //487

#define ERR_SYNTAXJOIN          " :Invalid JOIN syntax"                 //490
#define ERR_SYNTAXPART          " :Invalid PART syntax"                 //491
#define ERR_SYNTAXPRIVMSG       " :Invalid PRIVMSG syntax"              //492
#define ERR_SYNTAXKICK          " :Invalid KICK syntax"                 //493
#define ERR_SYNTAXINVITE        " :Invalid INVITE syntax"               //494
#define ERR_SYNTAXTOPIC         " :Invalid TOPIC syntax"                //495
#define ERR_SYNTAXMODE          " :Invalid MODE syntax"                 //496
#define ERR_SYNTAXMODEI         " :Invalid MODE Invite syntax"          //497
#define ERR_SYNTAXMODEK         " :Invalid MODE Password syntax"        //498
#define ERR_SYNTAXMODEL         " :Invalid MODE Limit syntax"           //499
#define ERR_SYNTAXMODEO         " :Invalid MODE Operator syntax"        //500
#define ERR_SYNTAXMODET         " :Invalid MODE Topic syntax"           //501
#define ERR_SYNTAXCHANNEL       " :Invalid CHANNEL - CHANNEL param requires '#' <#channel>" //502
#define ERR_SYNTAXQUIT          " :Invalid QUIT syntax"                 //503
#define ERR_SYNTAXEMPTYCOMMA    " :Empty after a comma"                 //504

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
        {390, ERR_ALREADYPASS},
        {391, ERR_ALREADYNICK},
        {392, ERR_ALREADYUSER},
        {393, ERR_NOPASS},
        {394, ERR_NONICK},
        {395, ERR_NOUSER},
        {415, ERR_SIGNINPASS},
        {416, ERR_SIGNININVPASS},
        {417, ERR_SIGNINNICK},
        {418, ERR_SIGNINUSER},
        {401, ERR_NOSUCHNICK},
        {403, ERR_NOSUCHCHANNEL},
        {404, ERR_CANNOTSENDTOCHAN},
        {421, ERR_UNKNOWNCOMMAND},
        {431, ERR_NONICKNAMEGIVEN},
        {432, ERR_ERRONEUSNICKNAME},
        {433, ERR_NICKNAMEINUSE},
        {441, ERR_TARGETONCHANNEL},
        {442, ERR_USERNOTONCHANNEL},
        {443, ERR_USERONCHANNEL},
        {444, ERR_TARGNOTONSERVER},
        {445, ERR_TARGNOTONCHANNEL},
        {446, ERR_USERCANNOTBENULL},
        {447, ERR_USERNOTINVITED},
        {448, ERR_USERALRINVITED},
        {451, ERR_CHANNELALROPR},
        {452, ERR_CHANNELNOOPR},
        {453, ERR_CHANNELNOTONLYINV},
        {454, ERR_CHANNELALRINV},
        {455, ERR_CHANNELALRUNSETINV},
        {456, ERR_CHANNELREACHLIM},
        {457, ERR_CHANNELEMPTYTOPIC},
        {458, ERR_CHANNELEMPTYPASS},
        {459, ERR_CHANNELZEROLIMIT},
        {460, ERR_CANNOTKICKUS},
        {461, ERR_NEEDMOREPARAMS},
        {470, ERR_CHANNELINCRPASSWORD},
        {471, ERR_CHANNELISFULL},
        {473, ERR_CHANNELINVITEONLY},
        {475, ERR_CHANNELBADKEY},
        {481, ERR_NOPRIVILEGES},
        {482, ERR_CHANOPRIVSNEEDED},
        {483, ERR_TOPICEMPTY},
        {484, ERR_PASSWORDEMPTY},
        {485, ERR_EMPTYCMD},
        {486, ERR_WRONGCMD},
        {487, ERR_INVALIDPASSWORD},
        {490, ERR_SYNTAXJOIN},
        {491, ERR_SYNTAXPART},
        {492, ERR_SYNTAXPRIVMSG},
        {493, ERR_SYNTAXKICK},
        {494, ERR_SYNTAXINVITE},
        {495, ERR_SYNTAXTOPIC},
        {496, ERR_SYNTAXMODE},
        {497, ERR_SYNTAXMODEI},
        {498, ERR_SYNTAXMODEK},
        {499, ERR_SYNTAXMODEL},
        {500, ERR_SYNTAXMODEO},
        {501, ERR_SYNTAXMODET},
        {502, ERR_SYNTAXCHANNEL},
        {503, ERR_SYNTAXQUIT},
        {504,ERR_SYNTAXEMPTYCOMMA}
    };
};