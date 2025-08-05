/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infras.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:54:25 by htran-th          #+#    #+#             */
/*   Updated: 2025/08/06 00:26:38 by htran-th         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

bool launchServer(char* password, int *iport);
void setNonBlocking(int fd);