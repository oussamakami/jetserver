/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingChecks.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:46:06 by okamili           #+#    #+#             */
/*   Updated: 2024/03/01 19:23:37 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

bool	isConfigFile(const std::string &path)
{
	std::string	temp = "";

	for (size_t index = 0; path[index]; index++)
		temp += std::toupper(path[index]);
	if (temp.find("CONF") == std::string::npos)
	{
		notify(std::cerr, "%EInvalid file extension.");
		return (false);
	}
	return (true);
}

bool	fileExist(const std::string &path)
{
	std::ifstream	source(path.c_str());

	if (!source.is_open())
	{
		notify(std::cerr, "%EFile doesn't exist.");
		return (false);
	}
	return (true);
}

bool hasOneValue(const std::string &optionName, const std::string &Value, size_t &fileLine)
{
	if (split(Value, "|").size() != 1)
	{
		notify(std::cerr, "%EInvalid \"%s\" value at line %d.", optionName.c_str(), fileLine);
		notify(std::cerr, "The \"%s\" option accepts only one value.", optionName.c_str());
		return (false);
	}
	return (true);
}
