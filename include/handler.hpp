/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 01:28:47 by siuol             #+#    #+#             */
/*   Updated: 2025/07/25 10:32:26 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

void    handlerJoin(Client* user, Channel* channel);

void    handlerPrivmsg(Client* user, Channel* channel, const std::string& msg);

void    handlerPart(Client* user, Channel* channel);

void    handlerKick(Client* user, Channel* channel, Client* targetUser);

void    handlerInvite(Client* user, Channel* channel, Client* targetUser);

void    handlerTopic(Client* user, Channel* channel, const std::string& topic);

void    handlerModeI(Client* user, Channel* channel, bool mode);

void    handlerModeT(Client* user, Channel* channel, bool mode);

void    handlerModeK(Client* user, Channel* channel, const std::string& password);

void    handlerModeO(Client* user, Channel* channel, bool mode);

void    handlerModeL(Client* user, Channel* channel, unsigned int limit);