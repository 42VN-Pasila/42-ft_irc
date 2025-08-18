/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:24:18 by caonguye          #+#    #+#             */
/*   Updated: 2025/08/18 18:33:02 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

int main(int ac, char** av)
{
    try
    {
        int iport;
        parseProgram(ac, av, &iport);
        launchServer(av[2], &iport);
    }
    catch(const std::exception& e)
    {
        LOG_ERROR(e.what());
        std::cout << std::endl;
    } 
}