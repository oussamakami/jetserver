/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestData.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:11:27 by okamili           #+#    #+#             */
/*   Updated: 2024/03/29 10:06:21 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestData.hpp"

RequestData::RequestData(void)
{
	this->_clientIP = "";
	this->_size = 0;
	this->_method = "";
	this->_path = "";
	this->_protocol = "";
	this->_host = "";
	this->_keep_alive = false;
	this->_server = NULL;
}

RequestData::RequestData(const std::string &clientIP) :
	_clientIP(clientIP)
{
	this->_size = 0;
	this->_method = "";
	this->_path = "";
	this->_protocol = "";
	this->_host = "";
	this->_keep_alive = false;
	this->_server = NULL;
}

RequestData::~RequestData(void)
{

}

void	RequestData::setSize(size_t newsize)
{
	this->_size = newsize;
}

void	RequestData::setIP(const std::string &newIP)
{
	this->_clientIP = newIP;
}

void	RequestData::setMethod(const std::string &method)
{
	if (method == "GET" || method == "POST" || method == "DELETE")
		this->_method = method;
	else
		this->_method = "";
}

void	RequestData::setProtocol(const std::string &proto)
{
	this->_protocol = proto;
}

void	RequestData::setHost(const std::string &host)
{
	this->_host = host;
}

void	RequestData::stayAlive(bool status)
{
	this->_keep_alive = status;
}

const size_t		RequestData::getSize(void) const
{
	return (this->_size);
}

const std::string	RequestData::getIP(void) const
{
	return (this->_clientIP);
}

const std::string	RequestData::getMethod(void) const
{
	return (this->_method);
}

const std::string	RequestData::getPath(void) const
{
	return (this->_path);
}

const std::string	RequestData::getProtocol(void) const
{
	return (this->_protocol);
}

const std::string	RequestData::getHost(void) const
{
	return (this->_host);
}

const bool			RequestData::isStayAlive(void) const
{
	return (this->_keep_alive);
}

Servers				&RequestData::getServer(void)
{
	return (*this->_server);
}
