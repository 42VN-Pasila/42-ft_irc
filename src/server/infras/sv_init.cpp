/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_init.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:56:30 by htran-th          #+#    #+#             */
/*   Updated: 2025/08/04 22:51:36 by htran-th         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

bool launchServer(char* password, int *iport)
{
    Server server(*iport, password);
    
    try {
        server.initSocket();
        server.bindAndListen();
    } catch(const std::exception& e) {
        throw ;
        return false;
    } 
    return true;
}