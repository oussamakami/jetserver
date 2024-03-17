/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseServers.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:55:23 by okamili           #+#    #+#             */
/*   Updated: 2024/03/17 01:27:32 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

static bool	checkOption(const std::vector<std::string> &option, size_t &fileLine)
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

static void	setDomainName(Servers *Data, const std::string &DomainName)
{
	std::vector<std::string>			Domains;
	std::vector<std::string>::iterator	it;
	
	Domains = extractOption(DomainName, "|");
	it = Domains.begin();
	while (it != Domains.end())
	{
		Data->addDomain(*it);
		it++;
	}
}

static bool	setPortValue(Servers *Data, const std::string &Value, size_t &fileLine)
{
	std::stringstream	ss;
	size_t				PortValue;

	if (!hasOneValue("DEVMODE", Value, fileLine))
		return (false);

	ss << Value;
	ss >> PortValue;
	if (ss.fail() || Value[0] == '-' || PortValue > 65535)
	{
		notify(std::cerr, "%EInvalid \"PORT\" value at line %d.", fileLine);
		return (false);
	}
	Data->setPort(PortValue);
	return (true);
}

static bool	extractErrorCode(const std::string &optionName, size_t &fileLine, size_t &HTTPCode)
{
	std::stringstream	ss;
	size_t				ErrorCode;

	ss << optionName.substr(6);
	ss >> ErrorCode;
	if (ss.fail() || ErrorCode < 400 || ErrorCode > 599)
	{
		notify(std::cerr, "%EInvalid \"%s\" option at line %d.", optionName.c_str(), fileLine);
		notify(std::cerr, "%IOptions are only valid for HTTP statuses between ERROR_4XX and ERROR_5XX.");
		return (false);
	}
	HTTPCode = ErrorCode;
	return (true);
}

static bool	setErrorPage(Servers *Data, const std::vector<std::string> &option, size_t &fileLine)
{
	std::fstream	file;
	size_t			HTTPCode;

	if (!extractErrorCode(option.at(0), fileLine, HTTPCode) ||
		!hasOneValue(option.at(0), option.at(1), fileLine))
		return (false);
	file.open(option.at(1).c_str());
	if (!file.is_open())
	{
		notify(std::cerr, "%EPath for \"%s\" at line %d not found.", option.at(0).c_str(), fileLine);
		return (false);
	}
	Data->addError(HTTPCode, option.at(1));
	return (true);
}

static bool	assignServerConf(const std::vector<std::string> &option, std::ifstream &source, size_t &fileLine)
{
	static Servers		*Data;

	if (!Data)
	{
		Data = new Servers;
		if (global::servers)
		{
			Data->setHost(global::servers->getHost());
			Data->setPort(global::servers->getPort());
			global::servers->setNext(Data);
		}
		else
			global::servers = Data;
	}
	
	if (option.at(0) == "END_SERVER")
		Data = NULL;
	else if (option.at(0) == "START_ROUTE")
		return (parseRoutes(source, ++fileLine));
	else if (option.at(0) == "HOST")
	{
		if (!hasOneValue(option.at(0), option.at(1), fileLine))
			return (false);
		Data->setHost(option.at(1));
	}
	else if (option.at(0) == "DOMAIN")
		setDomainName(Data, option.at(1));
	else if (option.at(0) == "PORT")
	{
		if (!setPortValue(Data, option.at(1), fileLine))
			return (false);
	}
	else if (option.at(0).length() == 9 && option.at(0).substr(0, 6) == "ERROR_")
	{
		if (!setErrorPage(Data, option, fileLine))
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

bool	parseServers(std::ifstream &source, size_t &fileLine)
{
	std::string					trimedStr;
	std::vector<std::string>	option;

	while(getline(source, trimedStr))
	{
		trimedStr = trim(trimedStr, "\t\r\n\"'; |");
		if (trimedStr.empty() || trimedStr[0] == '#')
			continue;

		option.clear();
		option = extractOption(trimedStr, "=");

		if (!checkOption(option, fileLine) || !assignServerConf(option, source, fileLine))
			return (false);

		if (option.at(0) == "END_SERVER")
			break;
		++fileLine;
	}
	return (true);
}
