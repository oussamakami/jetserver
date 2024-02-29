/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingChecks.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:46:06 by okamili           #+#    #+#             */
/*   Updated: 2024/02/29 05:53:13 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

bool	isConfigFile(std::string path)
{
	for (size_t index = 0; path[index]; index++)
		path[index] = std::toupper(path[index]);
	if (path.find("CONF") == std::string::npos)
	{
		notify(std::cerr, "%EInvalid file extension.");
		return (false);
	}
	return (true);
}

bool	fileExist(std::string path)
{
	std::ifstream	source(path.c_str());
	
	if (!source.is_open())
	{
		notify(std::cerr, "%EFile doesn't exist.");
		return (false);
	}
	source.close();
	return (true);
}