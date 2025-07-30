/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_system.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siuol <siuol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:58:36 by siuol             #+#    #+#             */
/*   Updated: 2025/07/31 02:16:39 by siuol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"

bool    prs_validPassword(char *av)
{
    std::string password = std::to_string(*av);
    
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

bool    prs_validPort(char *av)
{
    int                 value;
    std::string         port = std::to_string(*av);
    
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
    if (6000 < value && value < 7000)
    {
        throw std::runtime_error("Invalid arguments : Port range is only 6000-7000");
        return false;
    }
    return true;
}

bool    prs_program(int ac, char **av)
{
    if (ac != 3)
    {
        throw std::runtime_error("Invalid arguments : Start program by ./irc <port_number> <password>");
        std::cout << std::endl;
        return false;
    }
    if (!prs_validPort(*av + 1))
        return false;
    if (!prs_validPassword(*av + 2))
        return false;
    return true;
}