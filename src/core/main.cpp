/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:24:18 by caonguye          #+#    #+#             */
/*   Updated: 2025/08/02 18:25:58 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "systeem.hpp"

int main(int ac, char** av)
{
    try
    {
        prs_program(ac, av);
    }
    catch(const std::exception& e)
    {
        LOG_RED(e.what());
        std::cout << std::endl;
    }
    
}