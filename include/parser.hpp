/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 02:23:59 by siuol             #+#    #+#             */
/*   Updated: 2025/08/06 20:22:51 by htran-th         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

//System
bool                        parseProgram(int ac, char **av, int* iport);
bool                        parseValidPass(char *av);
bool                        parseValidNumber(std::string& nbr);
std::vector<std::string>    parseSplit(std::string& cmd);
std::vector<std::string>    parseSplitComma(std::string& cmd);
