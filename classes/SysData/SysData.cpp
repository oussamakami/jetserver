/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SysData.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:16:14 by okamili           #+#    #+#             */
/*   Updated: 2024/03/09 17:41:05 by okamili          ###   ########.fr       */
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
	std::vector<int>::iterator	it;

	if (this->_LogFile.is_open())
		this->_LogFile.close();

	notify(std::cout, "%IClosing Socket connections.");

	it = this->sockets.begin();
	while (it != this->sockets.end())
	{
		close(*it);
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
	if (socketFd != 1)
		this->sockets.push_back(socketFd);
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

const std::vector<int>	&SysData::getSockets(void) const
{
	return (this->sockets);	
}

bool	SysData::DevMode(void) const
{
	return (this->_DevMode);
}
