/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SysData.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:16:14 by okamili           #+#    #+#             */
/*   Updated: 2024/03/01 09:57:41 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SysData.hpp"

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
	if (this->_LogFile.is_open())
		this->_LogFile.close();
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
	if (this->_LogPath.empty())
		return (std::cout);
	if (!this->_LogFile.is_open())
		this->_LogFile.open(_LogPath.c_str(), std::ios::out | std::ios::app);
	return (this->_LogFile);
}

bool	SysData::DevMode(void) const
{
	return (this->_DevMode);
}
