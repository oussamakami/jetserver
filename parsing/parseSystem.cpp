/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseSystem.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:46:02 by okamili           #+#    #+#             */
/*   Updated: 2024/06/06 16:00:08 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

std::vector<std::string> extractOption(const std::string &trimedStr, const std::string &sep)
{
	std::vector<std::string>			Result;
	std::vector<std::string>::iterator	it;

	Result = split(trimedStr, sep);
	it = Result.begin();
	while (it != Result.end())
	{
		*it = trim(*it, "\t\r\n\"'; |");
		if ((*it).empty())
			it = Result.erase(it);
		else
			it++;
	}
	return (Result);
}

static bool	checkOption(const std::vector<std::string> &option, size_t &fileLine)
{
	if (option.size() != 2)
	{
		notify(std::cerr, "%EOption \"%s\" Undefined at Line %d.", option.at(0).c_str(), fileLine);
		return (false);
	}
	return (true);
}

static bool	setBodySize(const std::string &Value, size_t &fileLine)
{
	std::stringstream	ss;
	size_t				size;

	if (!hasOneValue("BODYSIZE", Value, fileLine))
		return (false);
	ss << Value;
	ss >> size;
	if (ss.fail() || Value[0] == '-')
	{
		notify(std::cerr, "%EInvalid \"BODYSIZE\" value at line %d.", fileLine);
		return (false);
	}
	global::system->setMaxBodySize(size);
	return (true);
}

static bool	setDevMode(const std::string &Value, size_t &fileLine)
{
	std::string	temp = "";

	if (!hasOneValue("DEVMODE", Value, fileLine))
		return (false);

	for (size_t index = 0; Value[index]; index++)
		temp += std::toupper(Value[index]);
	if (temp == "TRUE")
		global::system->setDevMode(true);
	else if (temp == "FALSE")
		global::system->setDevMode(false);
	else
	{
		notify(std::cerr, "%EInvalid \"DEVMODE\" value at line %d.", fileLine);
		return (false);
	}
	return (true);
}
static bool	assignSystemConf(const std::vector<std::string> &option, size_t &fileLine)
{
	if (option.at(0) == "LOG")
	{
		if (!hasOneValue(option.at(0), option.at(1), fileLine))
			return (false);
		global::system->setLogPath(option.at(1));
	}
	else if (option.at(0) == "CGI")
	{
		if (!hasOneValue(option.at(0), option.at(1), fileLine))
			return (false);
		global::system->set_CGI(option.at(1));
	}
	else if (option.at(0) == "CGI_EXTENTION")
	{
		if (!hasOneValue(option.at(0), option.at(1), fileLine))
			return (false);
		if (global::system->get_CGI().empty())
		{
			notify(std::cerr, "%E\"CGI_EXTENTION\" is declared before \"CGI\" at line %d.",
				fileLine);
			return (false);
		}
		global::system->set_CGI_Ext(trim(option.at(1), "."));
	}
	else if (option.at(0) == "BODYSIZE")
	{
		if (!setBodySize(option.at(1), fileLine))
			return (false);
	}
	else if (option.at(0) == "DEVMODE")
	{
		if (!setDevMode(option.at(1), fileLine))
			return (false);
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
	std::vector<std::string>	option;
	std::string					trimedStr;

	while (getline(source, trimedStr))
	{
		trimedStr = trim(trimedStr, "\t\r\n\"'; |");
		if (trimedStr.empty() || trimedStr[0] == '#')
			continue;

		if (trimedStr == "END_SYSTEM")
			break;

		option.clear();
		option = extractOption(trimedStr, "=");

		if (!checkOption(option, fileLine) || !assignSystemConf(option, fileLine))
			return (false);
		++fileLine;
	}
	return (true);
}
