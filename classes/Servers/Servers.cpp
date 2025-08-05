/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:31:32 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 12:25:24 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Servers.hpp"
#include "../../tools/tools.hpp"

static bool	isIPV4(const std::string &host)
{
	std::vector<std::string>	combinations;
	std::string					*iterator;
	int							temp;

	combinations = split(host, ".");
	if (combinations.size() != 4)
		return (false);

	iterator = &combinations[0];
	for (int index = 0; index < 4; index++)
	{
		temp = StringToInt(iterator[index]);
		if (iterator[index].length() > 3 || temp > 255 || temp < 0)
			return (false);
	}
	return (true);
}

static const std::string	generateErrorPage(const size_t errorNum, const std::string &msg)
{
	std::stringstream	result;

	result << "<!DOCTYPE html><html lang=\"en\"><head><title>HTTP " << errorNum;
	result << "</title></head><body><center><h1 style=\"font-family: sans-serif;\">";
	if (msg.empty())
		result << "HTTP Error Code: " << errorNum << "</h1><hr><h3 style=\"font-family:";
	else
		result << errorNum << " - " << msg << "</h1><hr><h3 style=\"font-family:";
	result << " monospace;\">JetServer v1.0</h3></center></body></html>";
	
	

	return (result.str());
}

Servers::Servers(void)
{
	this->_Port = 8080;
	this->_Host = "0.0.0.0";
}

Servers::~Servers(void)
{
	std::vector<Locations *>::iterator it;

	it = this->_Routes.begin();
	while (it != this->_Routes.end())
	{
		delete (*it);
		it++;
	}
}

void	Servers::setPort(const uint16_t PortNum)
{
	this->_Port = PortNum;
}

void	Servers::setHost(const std::string &Host)
{
	this->_Host = Host;
	addDomain(this->_Host);
}

void	Servers::addDomain(const std::string &DomainName)
{
	std::string	lowerCaseDomain = "";

	for (size_t index = 0; DomainName[index]; index++)
		lowerCaseDomain += std::tolower(DomainName[index]);

	this->_Domain.insert(lowerCaseDomain);
}

void	Servers::addError(const size_t errorNum, const std::string &errorPath)
{
	this->_ErrorPages[errorNum] = errorPath;
}

void	Servers::setRoutes(Locations *Route)
{
	this->_Routes.push_back(Route);
}

uint16_t	Servers::getPort(void) const
{
	return (this->_Port);
}

const std::string	&Servers::getHost(void) const
{
	return (this->_Host);
}

bool	Servers::hasDomain(const std::string &DomainName) const
{
	std::string	lowerCaseDomain = "";

	for (size_t index = 0; DomainName[index]; index++)
		lowerCaseDomain += std::tolower(DomainName[index]);

	if (isIPV4(lowerCaseDomain))
	{
		if (this->_Host == "0.0.0.0" || lowerCaseDomain == this->_Host)
			return (true);
	}
	return (this->_Domain.find(lowerCaseDomain) != this->_Domain.end());
}

const std::set<std::string>	&Servers::getDomains(void) const
{
	return (this->_Domain);
}

const std::string	Servers::getError(const size_t errorNum, const std::string &msg)
{
	std::fstream		file;
	std::stringstream	result;

	if (this->_ErrorPages.find(errorNum) != this->_ErrorPages.end())
		file.open(this->_ErrorPages[errorNum].c_str(), std::ios::in);
	
	if (file.is_open())
	{
		result << file.rdbuf();
		file.close();
		return (result.str());
	}
	return (generateErrorPage(errorNum, msg));
}

Locations		*Servers::getRoute(const std::string &ReqPath)
{
	std::string					routePath;
	std::vector<std::string>	reqCombs;

	reqCombs = pathCombs(ReqPath);
	for (size_t i = 0; i < reqCombs.size(); i++)
	{
		for (size_t j = 0; j < this->_Routes.size(); j++)
		{
			routePath = pathCombs(this->_Routes.at(j)->getPath()).front();
			if (routePath == reqCombs.at(i))
				return (this->_Routes.at(j));
		}
	}
	return (NULL);
}