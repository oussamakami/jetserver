/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SysData.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:16:14 by okamili           #+#    #+#             */
/*   Updated: 2024/05/12 06:34:26 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SysData.hpp"
#include "../../tools/tools.hpp"

SysData::SysData(void)
{
	this->_maxBodySize = 16384;
	this->_CGI = "";
	this->_CGI_Ext = "";
	this->_UseCGI = false;
	this->_DevMode = true;
	this->_LogPath = "";
}

SysData::~SysData(void)
{
	std::vector<pollfd>::iterator	it;

	if (this->_LogFile.is_open())
		this->_LogFile.close();

	it = this->networkFDs.begin();
	while (it != this->networkFDs.end())
	{
		if (it == this->networkFDs.begin())
			notify(std::cout, "%IClosing Socket connections.");
		close(it->fd);
		it++;
	}
}

void	SysData::setMaxBodySize(const size_t newSize)
{
	this->_maxBodySize = newSize;
}

void	SysData::set_CGI(const std::string &CGI_Program)
{
	if (CGI_Program.empty())
	{
		this->_CGI = "";
		this->_CGI_Ext = "";
		this->_UseCGI = false;
		return ;
	}
	this->_CGI = CGI_Program;
	if (!this->_CGI_Ext.empty())
		this->_UseCGI = true;
}

void	SysData::set_CGI_Ext(const std::string &CGI_Extention)
{
	if (CGI_Extention.empty())
	{
		this->_CGI = "";
		this->_CGI_Ext = "";
		this->_UseCGI = false;
		return ;
	}
	this->_CGI_Ext = CGI_Extention;
	if (!this->_CGI.empty())
		this->_UseCGI = true;
}

void	SysData::setLogPath(const std::string &newLogPath)
{
	if (this->_LogFile.is_open())
		this->_LogFile.close();
	this->_LogPath = newLogPath;
}

void	SysData::addSocket(int socketFd)
{	
	pollfd temp;

	if (socketFd != -1)
	{
		temp.events = POLLIN;
		temp.fd = socketFd;
		this->networkFDs.push_back(temp);
		this->sockets.insert(socketFd);
	}
}

void	SysData::addClient(int clientFd, const std::string &clientIP)
{
	pollfd temp;

	if (clientFd != -1)
	{
		temp.events = POLLIN | POLLERR;
		temp.fd = clientFd;
		this->networkFDs.push_back(temp);
		this->clientIP[clientFd] = clientIP;
	}
}

void	SysData::setDevMode(bool status)
{
	this->_DevMode = status;
}

size_t		SysData::getMaxSize(void) const
{
	return (this->_maxBodySize);
}

bool	SysData::use_CGI(void) const
{
	return (this->_UseCGI);
}

const std::string	&SysData::get_CGI(void) const
{
	return (this->_CGI);
}

const std::string	&SysData::get_CGI_Ext(void) const
{
	return (this->_CGI_Ext);
}

const std::string	&SysData::getLogPath(void) const
{
	return (this->_LogPath);
}

std::ostream	&SysData::getLogStream(void)
{
	static bool	printedWarning;

	if (!this->_LogFile.is_open())
	{
		this->_LogFile.open(_LogPath.c_str(), std::ios::out | std::ios::app);
		if (this->_LogPath.empty() || !this->_LogFile.is_open())
		{
			if (!printedWarning)
			{
				notify(std::cout, "%WUnable to open the log file or log file not provided. Falling back to standard output.");
				printedWarning = true;
			}
			return (std::cout);
		}
	}
	return (this->_LogFile);
}

std::set<int>	&SysData::getSockets(void)
{
	return (this->sockets);	
}

std::vector<pollfd>	&SysData::getNetworkFDs(void)
{
	return (this->networkFDs);
}

bool	SysData::DevMode(void) const
{
	return (this->_DevMode);
}

void	SysData::deleteClient(int clientfd)
{
	std::vector<pollfd>::iterator it;
	std::map<int, std::string>::iterator holder;

	holder = this->clientIP.find(clientfd);
	if (holder == this->clientIP.end())
		return ;

	this->clientIP.erase(holder);
	it = this->networkFDs.begin();
	while (it != this->networkFDs.end())
	{
		if (it->fd == clientfd)
		{
			this->networkFDs.erase(it);
			break;
		}
		it++;
	}
	close(clientfd);
}

const std::string	SysData::getClientIP(int fd)
{
	std::map<int, std::string>::iterator holder;

	holder = this->clientIP.find(fd);
	if (holder != this->clientIP.end())
		return (holder->second);
	return ("");
}
