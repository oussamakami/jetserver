/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SysData.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:16:14 by okamili           #+#    #+#             */
/*   Updated: 2024/07/01 06:41:59 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SysData.hpp"
#include "../../tools/tools.hpp"

SysData::SysData(void)
{
	std::fstream webini;

	this->_maxBodySize = 52428800;
	this->_CGI = "";
	this->_CGI_Ext = "";
	this->_UseCGI = false;
	this->_DevMode = true;
	this->_LogPath = "";

	webini.open("/tmp/web.ini", std::ios::out);
	if (webini.is_open())
	{
		webini << "post_max_size = 52428800\n";
		webini << "upload_max_filesize = 52428800\n";
	}
	webini.close();
}

SysData::~SysData(void)
{
	std::vector<pollfd>::iterator			networkIterator;
	std::map<int, RequestData *>::iterator	requestsIterator;
	std::map<int, ResponseData *>::iterator	responseIterator;

	if (this->_LogFile.is_open())
		this->_LogFile.close();
	std::remove("/tmp/web.ini");

	for (networkIterator = this->networkFDs.begin(); networkIterator != this->networkFDs.end(); networkIterator++)
	{
		if (networkIterator == this->networkFDs.begin())
			notify(std::cout, "%IClosing Socket connections.");
		close(networkIterator->fd);
	}
	for (requestsIterator = this->Requests.begin(); requestsIterator != this->Requests.end(); requestsIterator++)
		delete (requestsIterator->second);
	for (responseIterator = this->Responses.begin(); responseIterator != this->Responses.end(); responseIterator++)
		delete (responseIterator->second);
}

void	SysData::setMaxBodySize(const size_t newSize)
{
	std::fstream webini;

	this->_maxBodySize = newSize;

	webini.open("/tmp/web.ini", std::ios::out);
	if (webini.is_open())
	{
		webini << "post_max_size = " << intToString(newSize);
		webini << "\nupload_max_filesize = " << intToString(newSize);
		webini << "\n";
	}
	webini.close();
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
	std::vector<pollfd>::iterator			it;
	std::map<int, std::string>::iterator	holder;

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

std::map<int, RequestData *>	&SysData::getRequestPackets(void)
{
	return (this->Requests);
}

std::map<int, ResponseData *>	&SysData::getResponsePackets(void)
{
	return (this->Responses);
}