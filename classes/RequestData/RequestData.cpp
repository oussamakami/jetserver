/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestData.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:11:27 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 12:08:31 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestData.hpp"

static std::string	extractQueryString(std::string &path)
{
	std::string	QueryString;
	
	if (path.find_first_of('?') == std::string::npos)
		return ("");
	
	QueryString = path.substr(path.find_first_of('?') + 1);
	path = path.substr(0, path.find_first_of('?'));

	return (QueryString);
}

static std::string	generateFullPath(const std::string &requestPath, const std::string &routePath)
{
	std::string	result;

	result = routePath;
	if (result[result.length() - 1] == '/')
		result.erase(result.length() - 1);
	result += requestPath;
	return (result);
}

RequestData::RequestData(void)
{
	this->_Size = 0;
	this->_ClientIP = "";
	this->_Method = "";
	this->_Path = "";
	this->_Protocol = "";
	this->_Body = "";
	this->_Server = NULL;
}

RequestData::RequestData(const std::string &clientIP) :
	_ClientIP(clientIP)
{
	this->_Size = 0;
	this->_Method = "";
	this->_Path = "";
	this->_Protocol = "";
	this->_Body = "";
	this->_Server = NULL;
}

RequestData::~RequestData(void)
{

}

void	RequestData::setSize(size_t newsize)
{
	this->_Size = newsize;
}

void	RequestData::setClientIP(const std::string &newIP)
{
	this->_ClientIP = newIP;
}

void	RequestData::setMethod(const std::string &method)
{
	if (method == "GET" || method == "POST" || method == "DELETE")
		this->_Method = method;
	else
		this->_Method = "";
}

void	RequestData::setPath(const std::string &path)
{
	std::string	filteredString;

	filteredString = path;
	
	this->addMetaData("QueryString", extractQueryString(filteredString));
	this->_Path = filteredString;
}

void	RequestData::setProtocol(const std::string &protocol)
{
	this->_Protocol = protocol;
}

void	RequestData::appendBody(const std::string &data)
{
	this->_Body += data;
}

void	RequestData::addMetaData(const std::string &key, const std::string &value)
{
	if (!key.empty() && !value.empty())
		this->_MetaData[key] = value;
}

void	RequestData::setServer(Servers *Data)
{
	this->_Server = Data;
	
	if (Data)
	{
		this->_Route = Data->getRoute(this->getPath());
		this->_FullPath = generateFullPath(this->getPath(), this->_Route->getRoot());
	}
}

size_t		RequestData::getSize(void) const
{
	return (this->_Size);
}

const std::string	RequestData::getClientIP(void) const
{
	return (this->_ClientIP);
}

const std::string	RequestData::getMethod(void) const
{
	return (this->_Method);
}

const std::string	RequestData::getPath(void) const
{
	return (this->_Path);
}

const std::string	RequestData::getFullPath(void) const
{
	return (this->_FullPath);
}

const std::string	RequestData::getProtocol(void) const
{
	return (this->_Protocol);
}

const std::string	RequestData::getBody(void) const
{
	return (this->_Body);
}

const std::string	RequestData::getMetaData(const std::string &key) const
{
	if (!key.empty() && this->_MetaData.find(key) != this->_MetaData.end())
		return (this->_MetaData.find(key)->second);
	return ("");
}

Servers			*RequestData::getServer(void)
{
	return (this->_Server);
}

Locations		*RequestData::getRoute(void)
{
	return (this->_Route);
}