/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:31:32 by okamili           #+#    #+#             */
/*   Updated: 2024/05/12 12:17:11 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Servers.hpp"
#include "../../tools/tools.hpp"
 
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

static const std::string	generateErrorPage(const size_t errorNum)
{
	std::stringstream	result;

	result << "<!DOCTYPE html><html lang=\"en\"><head><title>HTTP " << errorNum;
	result << "</title></head><body><center><h1 style=\"font-family: sans-serif;\">";
	result << "HTTP Error Code: " << errorNum << "</h1><hr><h3 style=\"font-family:";
	result << " monospace;\">webServer v1.0</h3></center></body></html>";

	return (result.str());
}

const bool	Servers::hasDomain(const std::string &DomainName) const
{
	std::string	lowerCaseDomain = "";

	for (size_t index = 0; DomainName[index]; index++)
		lowerCaseDomain += std::tolower(DomainName[index]);

	return (this->_Domain.find(lowerCaseDomain) != this->_Domain.end());
}

const std::set<std::string>	&Servers::getDomains(void) const
{
	return (this->_Domain);
}

const std::string	Servers::getError(const size_t errorNum)
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
	return (generateErrorPage(errorNum));
}

const Locations		*Servers::getRoute(const std::string &ReqPath) const
{
	std::string	routePath;
	std::vector<std::string>	reqCombs;

	reqCombs = pathCombs(ReqPath);
	for (int i = 0; i < reqCombs.size(); i++)
	{
		for (int j = 0; j < this->_Routes.size(); j++)
		{
			routePath = pathCombs(this->_Routes.at(j)->getPath()).front();
			if (routePath == reqCombs.at(i))
				return (this->_Routes.at(j));
		}
	}
	return (NULL);
}
