/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_socket_init.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:35:59 by htran-th          #+#    #+#             */
/*   Updated: 2025/08/04 22:36:13 by htran-th         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

void Server::initSocket() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        throw std::runtime_error("Server: socket creating failed!");
    }
}