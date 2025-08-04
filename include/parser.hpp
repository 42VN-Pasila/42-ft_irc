/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 02:23:59 by siuol             #+#    #+#             */
/*   Updated: 2025/08/04 02:56:34 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

//System
bool                        parseProgram(int ac, char **av);
bool                        parseValidPass(char *av);
std::vector<std::string>    parseSplit(std::string& cmd);
std::vector<std::string>    parseSplitComma(std::string& cmd);