/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 02:23:59 by siuol             #+#    #+#             */
/*   Updated: 2025/08/02 17:59:11 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "system.hpp"

//System
bool                        prs_program(int ac, char **av);
bool                        prs_validPassword(char *av);
std::vector<std::string>    split(std::string& cmd);