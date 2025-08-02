/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:24:18 by caonguye          #+#    #+#             */
/*   Updated: 2025/08/02 18:50:08 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

int main(int ac, char** av)
{
    try
    {
        prs_program(ac, av);
        // Tao Server()
        // ket noi socket vao server
    }
    catch(const std::exception& e)
    {
        LOG_ERROR(e.what());
        std::cout << std::endl;
    } 
}