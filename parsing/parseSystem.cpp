/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseSystem.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:46:02 by okamili           #+#    #+#             */
/*   Updated: 2024/02/29 12:45:42 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

static std::vector<std::string> extractOption(std::string holder)
{
	std::vector<std::string> result;

	result = split(holder, "=");
	std::vector<std::string>::iterator it = result.begin();
	while (it != result.end())
	{
		*it = trim(*it, "\t\r\n\"'; ");
		if (*it == "")
			it = result.erase(it);
		else
			it++;
	}
	return (result);
}

static bool	checkOption(std::vector<std::string> option, size_t fileLine)
{
	if (option.size() != 2)
	{
		notify(std::cerr, "%EOption \"%s\" Undefined at Line %d.", option.at(0).c_str(), fileLine);
		return (false);
	}
	return (true);
}

static bool	assignSystemConf(std::vector<std::string> option, size_t fileLine)
{
	std::stringstream ss;
	size_t	size;
	std::string upperBool = "";
	
	if (option.at(0) == "LOG")
		global::system->setLogPath(option.at(1));
	else if (option.at(0) == "CGI")
	{
		if (split(option.at(1), " ").size() != 1 || split(option.at(1), ",").size() != 1)
		{
			notify(std::cerr, "%EInvalid \"CGI\" value at line %d.", fileLine);
			notify(std::cerr, "%IThe \"CGI\" option accepts only one value.");
			return (false);
		}
		global::system->set_CGI(option.at(1));
	}
	else if (option.at(0) == "CGI_EXTENTION")
	{
		if (split(option.at(1), " ").size() != 1 || split(option.at(1), ",").size() != 1)
		{
			notify(std::cerr, "%EInvalid \"CGI_EXTENTION\" value at line %d.", fileLine);
			notify(std::cerr, "%IThe \"CGI_EXTENTION\" option accepts only one value.");
			return (false);
		}
		global::system->set_CGI_Ext(trim(option.at(1), "."));
	}
	else if (option.at(0) == "BODYSIZE")
	{
		ss << option.at(1);
		ss >> size;
		if (ss.fail() || option.at(1)[0] == '-')
		{
			notify(std::cerr, "%EInvalid \"BODYSIZE\" value at line %d.", fileLine);
			return (false);
		}
		global::system->setMaxBodySize(size);
	}
	else if (option.at(0) == "DEVMODE")
	{
		for (size_t index = 0; option.at(1)[index]; index++)
			upperBool += std::toupper(option.at(1)[index]);
		if (upperBool == "TRUE")
			global::system->setDevMode(true);
		else if (upperBool == "FALSE")
			global::system->setDevMode(false);
		else
		{
			notify(std::cerr, "%EInvalid \"DEVMODE\" value at line %d.", fileLine);
			return (false);
		}
	}
	else
	{
		notify(std::cerr, "%EUnknown option \"%s\" encountered at line %d.",
			option.at(0).c_str(), fileLine);
		return (false);
	}
	return (true);
}

bool	parseSystem(std::ifstream &source, size_t &fileLine)
{
	std::string		holder;
	std::vector<std::string> option;

	for (fileLine++; getline(source, holder); fileLine++)
	{
		holder = trim(holder, "\t\r\n ");
		if (holder.empty() || holder[0] == '#')
			continue;
		if (holder == "END_SYSTEM")
			break;
		option.clear();
		option = extractOption(holder);
		if (!checkOption(option, fileLine) || !assignSystemConf(option, fileLine))
			return (false);
	}
	return (true);
}
