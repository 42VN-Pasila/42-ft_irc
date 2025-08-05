/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:24:18 by caonguye          #+#    #+#             */
/*   Updated: 2025/08/05 18:26:20 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

int main(int ac, char** av)
{
    try
    {
        prs_program(ac, av);
		
		unsigned int port = static_cast<unsigned int>(std::atoi(av[1]));
    	std::string password = av[2];

        // Tao Server()
		Server server(port, password);
		server.setupSocket();
        // ket noi socket vao server
		// server.run();
    }
    catch(const std::exception& e)
    {
        LOG_INFO(e.what());
        std::cout << std::endl;
    } 
}