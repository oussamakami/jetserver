/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseRoutes.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:41:51 by okamili           #+#    #+#             */
/*   Updated: 2024/03/17 06:37:47 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

static bool	checkOption(const std::vector<std::string> &option, size_t &fileLine)
{
	if (option.at(0) == "END_ROUTE")
	{
		if (option.size() != 1)
			notify(std::cerr, "%EUnknown Option \"%s = %s\" on Line %d.", option.at(0).c_str(),
					option.at(1).c_str(), fileLine);
		return (option.size() == 1);	
	}
	if (option.size() != 2)
	{
		notify(std::cerr, "%EOption \"%s\" Undefined at Line %d.", option.at(0).c_str(), fileLine);
		return (false);
	}
	return (true);
}

static void	setIndexValues(Locations *Route, const std::string &Values)
{
	std::vector<std::string>			fileNames;
	std::vector<std::string>::iterator	it;

	fileNames = extractOption(Values, "|");
	it = fileNames.begin();
	while (it != fileNames.end())
	{
		Route->addIndex(*it);
		it++;
	}
}

static bool	setBrowsingStatus(Locations *Route, const std::string &Status, size_t &fileLine)
{
	std::string	temp = "";

	if (!hasOneValue("BROWSEDIR", Status, fileLine))
		return (false);

	for (size_t index = 0; Status[index]; index++)
			temp += std::toupper(Status[index]);

	if (temp == "TRUE")
		Route->setBrowsing(true);
	else if (temp == "FALSE")
		Route->setBrowsing(false);
	else
	{
		notify(std::cerr, "%EInvalid \"BROWSEDIR\" value at line %d.", fileLine);
		return (false);
	}
	return (true);
}

static bool	setMethods(Locations *Route, const std::string &Values, size_t &fileLine)
{
	std::vector<std::string>			Methods;
	std::vector<std::string>::iterator	it;

	Methods = extractOption(Values, "|");
	it = Methods.begin();
	while (it != Methods.end())
	{
		for (size_t index = 0; (*it)[index]; index++)
			(*it)[index] = std::toupper((*it)[index]);
		it++;
	}
	it = Methods.begin();
	while (it != Methods.end())
	{
		if (!Route->setMethod(*it, true))
		{
			notify(std::cerr, "%EInvalid \"METHODS\" value \"%s\" at line %d.", (*it).c_str(), fileLine);
			return (false);
		}
		it++;
	}
	return (true);
}

static bool	assignRouteConf(const std::vector<std::string> &option, size_t &fileLine)
{
	static Locations	*Route;

	if (!Route)
	{
		Route = new Locations(global::system->DevMode());
		global::servers->back()->setRoutes(Route);
	}

	if (option.at(0) == "END_ROUTE")
		Route = NULL;
	else if (option.at(0) == "REQ_PATH")
	{
		if (!hasOneValue(option.at(0), option.at(1), fileLine))
			return (false);
		Route->setPath(option.at(1));
	}
	else if (option.at(0) == "ROOT")
	{
		if (!hasOneValue(option.at(0), option.at(1), fileLine))
			return (false);
		Route->setRoot(option.at(1));
	}
	else if (option.at(0) == "INDEX")
		setIndexValues(Route, option.at(1));
	else if (option.at(0) == "REDIRECT")
	{
		if (!hasOneValue(option.at(0), option.at(1), fileLine))
			return (false);
		Route->setRedirection(option.at(1));
	}
	else if (option.at(0) == "METHODS")
	{
		if (!setMethods(Route, option.at(1), fileLine))
			return (false);
	}
	else if (option.at(0) == "BROWSEDIR")
	{	
		if (!hasOneValue(option.at(0), option.at(1), fileLine) || 
			!setBrowsingStatus(Route, option.at(1), fileLine))
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

bool	parseRoutes(std::ifstream &source, size_t &fileLine)
{
	std::vector<std::string>	option;
	std::string					trimedStr;

	while (getline(source, trimedStr))
	{
		trimedStr = trim(trimedStr, "\t\r\n\"'; |");
		if (trimedStr.empty() || trimedStr[0] == '#')
			continue;

		option.clear();
		option = extractOption(trimedStr, "=");

		if (!checkOption(option, fileLine) || !assignRouteConf(option, fileLine))
			return (false);

		if (option.at(0) == "END_ROUTE")
			break;
		++fileLine;
	}
	return (true);
}
