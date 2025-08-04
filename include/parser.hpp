/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 02:23:59 by siuol             #+#    #+#             */
/*   Updated: 2025/08/04 21:41:42 by htran-th         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

//System
bool                        prs_program(int ac, char **av, int *port);
bool                        prs_validPassword(char *av);
std::vector<std::string>    split(std::string& cmd);