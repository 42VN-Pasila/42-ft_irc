/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:24:18 by caonguye          #+#    #+#             */
/*   Updated: 2025/08/06 20:27:25 by htran-th         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

int main(int ac, char** av)
{
    try
    {
        int iport;
        parseProgram(ac, av, &iport);
        // ket noi socket vao server
        launchServer(av[2], &iport);
        
    }
    catch(const std::exception& e)
    {
        LOG_ERROR(e.what());
        std::cout << std::endl;
    } 
}