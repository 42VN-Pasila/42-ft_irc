/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_system.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htran-th <htran-th@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:58:36 by siuol             #+#    #+#             */
/*   Updated: 2025/08/04 21:41:08 by htran-th         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

bool    prs_validPassword(char *av)
{
    std::string password(av);
    
    if (password.empty())
    {
        throw std::runtime_error("Invalid password : Password must not be empty");
        return false;
    }
    if (password.length() > 10)
    {
        throw std::runtime_error("Invalid password : Password length must be <= 10");
        return false;
    }
    for (char c: password)
    {
        if (!std::isprint(c))
        {
            throw std::runtime_error("Invalid password : Password contains unprintable character");
            return false;
        }
    }
    return true;
}

static bool    prs_validPort(char *av, int *iport)
{
    int                 value;
    std::string         port(av);
    
    if (port.empty())
    {
        throw std::runtime_error("Invalid arguments : Port cannot be empty");
        return false;
    }
    
    auto    value_ptr = std::from_chars(port.data(), port.data() + port.length(), value);
    if (value_ptr.ec == std::errc::invalid_argument)
    {
        throw std::runtime_error("Invalid arguments : Port is not a valid integer");
        return false;
    }
    if (value_ptr.ec == std::errc::result_out_of_range)
    {
        throw std::runtime_error("Invalid arguments : Port is too large");
        return false;
    }
    if (value_ptr.ptr != port.data() + port.length())
    {
        throw std::runtime_error("Invalid arguments : Port is not a valid integer");
        return false;
    }
    if (value < 6000 || value > 7000)
    {
        throw std::runtime_error("Invalid arguments : Port range is only 6000-7000");
        return false;
    }
    *iport = value;
    return true;
}

bool    prs_program(int ac, char **av, int *iport)
{
    if (ac != 3)
    {
        throw std::runtime_error("Invalid arguments : Start program by ./irc <port_number> <password>");
        std::cout << std::endl;
        return false;
    }
    if (!prs_validPort(av[1], iport))
        return false;
    if (!prs_validPassword(av[2]))
        return false;
    return true;
}