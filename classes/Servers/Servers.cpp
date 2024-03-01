/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:31:32 by okamili           #+#    #+#             */
/*   Updated: 2024/03/01 20:01:45 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Servers.hpp"

Servers::Servers(void)
{
	this->_Port = 8080;
	this->_Host = "0.0.0.0";
	this->_Routes = NULL;
	this->_Next = NULL;
	this->_Prev = NULL;
}

Servers::~Servers(void)
{
	Servers	*head = this;
	Servers *tmp;

	if (head->_Prev)
		head->_Prev->_Next = NULL;

	while (head)
	{
		tmp = head->_Next;
		delete head->_Routes;
		if (head != this)
			delete head;
		head = tmp;
	}
}

void	Servers::setPort(const size_t PortNum)
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
	if (!this->_Routes)
		this->_Routes = Route;
	else
		this->_Routes->setNext(Route);
}

void	Servers::setNext(Servers *nextServer)
{
	Servers *tail = this;

	if (!nextServer)
		return ;
	while (tail->_Next)
		tail = tail->_Next;
	tail->_Next = nextServer;
	nextServer->_Prev = tail;
}

size_t	Servers::getPort(void) const
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

	result << "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\">";
	result << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
	result << "<title>HTTP STATUS " << errorNum;
	result << "</title><style>* {margin: 0;padding: 0;box-sizing: border-box;color: #fff;}";
	result << "body {height: 100vh;width: 100vw;background: #130635;padding: 2em;}";
	result << "body > section {width: 100\%;height: 95\%;display: grid;place-content: center;}";
	result << "h1 {font-size: 10em;text-align: center;font-family: sans-serif;line-height: .8em;}";
	result << "h3 {font-family: monospace;}</style></head><body><section><h1>" << errorNum;
	result << "<br>Error!!</h1></section><h3>webServer v1.0</h3></body></html>";

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

Servers	*Servers::getNext(void)
{
	return (this->_Next);
}

Servers	*Servers::getPrev(void)
{
	return (this->_Prev);
}
