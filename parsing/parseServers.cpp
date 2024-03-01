/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseServers.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:55:23 by okamili           #+#    #+#             */
/*   Updated: 2024/03/01 10:31:30 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

static bool	checkOption(std::vector<std::string> option, size_t fileLine)
{
	if (option.at(0) == "START_ROUTE" || option.at(0) == "END_SERVER")
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

static bool	assignServerConf(std::vector<std::string> option, size_t fileLine)
{
	static Servers	*Data;
	std::stringstream ss;
	size_t	numHolder;
	
	std::fstream file;
	
	if (!Data)
	{
		Data = new Servers;
		if (!global::servers)
			global::servers = Data;
		else
			global::servers->setNext(Data);
	}
	
	if (option.at(0) == "HOST")
		Data->setHost(option.at(1));
	else if (option.at(0) == "PORT")
	{
		ss.str("");
		ss << option.at(1);
		ss >> numHolder;
		if (ss.fail() || option.at(1)[0] == '-' || numHolder > 65535)
		{
			notify(std::cerr, "%EInvalid \"PORT\" value at line %d.", fileLine);
			return (false);
		}
		Data->setPort(numHolder);
	}
	else if (option.at(0) == "DOMAIN")
	{
		std::vector<std::string> domains;
		std::vector<std::string>::iterator it;
		
		domains = extractOption(option.at(1), "|");
		it = domains.begin();
		while (it != domains.end())
		{
			Data->addDomain(*it);
			it++;
		}
		domains.clear();
	}
	else if (option.at(0).length() == 9 && option.at(0).substr(0, 6) == "ERROR_")
	{
		ss.str("");
		ss << option.at(0).substr(6);
		ss >> numHolder;
		if (ss.fail() || numHolder < 400 || numHolder > 599)
		{
			notify(std::cerr, "%EInvalid \"%s\" option at line %d.", option.at(0).c_str(), fileLine);
			notify(std::cerr, "%IOptions are only valid for HTTP statuses between ERROR_4XX and ERROR_5XX.");
			return (false);
		}
		file.open(option.at(1).c_str());
		if (!file.is_open())
		{
			notify(std::cerr, "%EPath for \"%s\" at line %d not found.", option.at(0).c_str(), fileLine);
			return (false);
		}
		file.close();
		Data->addError(numHolder, option.at(1));
	}
	else if (option.at(0) == "END_SERVER")
		Data = NULL;
	else
	{
		notify(std::cerr, "%EUnknown option \"%s\" encountered at line %d.",
			option.at(0).c_str(), fileLine);
		return (false);
	}
	return (true);
	// else if (option.at(0) == "START_ROUTE")
	// {
	// 	Data = NULL;
	// 	notify(std::cout, "%Wadded server, need to program route dev.");
	// }
}

bool	parseServers(std::ifstream &source, size_t &fileLine)
{
	std::string		holder;
	std::vector<std::string> option;

	for (fileLine++; getline(source, holder); fileLine++)
	{
		holder = trim(holder, "\t\r\n ");
		if (holder.empty() || holder[0] == '#')
			continue;
		option.clear();
		option = extractOption(holder, "=");
		if (!checkOption(option, fileLine) || !assignServerConf(option, fileLine))
			return (false);
		if (option.at(0) == "END_SERVER")
			break;
	}
	return (true);
}
