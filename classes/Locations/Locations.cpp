/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Locations.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 02:38:09 by okamili           #+#    #+#             */
/*   Updated: 2024/03/01 08:58:44 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Locations.hpp"

static size_t	FindMethod(const std::string &method)
{
	std::string	UpperMethod = "";
	std::string List[3] = {"GET", "POST", "DELETE"};

	for (size_t index = 0; method[index]; index++)
		UpperMethod += std::toupper(method[index]);
	
	for (size_t index = 0; index < 3; index++)
	{
		if (UpperMethod == List[index])
			return (index);
	}
	return (-1);
}

Locations::Locations(bool sysDevMode)
{
	this->_PathReq = "";
	this->_Root = "";
	this->_UseGet = false;
	this->_UsePost = false;
	this->_UseDelete = false;
	this->_isRedirect = false;
	this->_BrowsDir = sysDevMode;
	this->_Redirection = "";
	this->_Prev = NULL;
	this->_Next = NULL;
	this->_Index = new std::vector<std::string>;
}

Locations::~Locations(void)
{
	Locations	*head = this;
	Locations	*tmp;

	while (head)
	{
		head->_Index->clear();
		delete head->_Index;
		tmp = head->_Next;
		if (head != this)
			delete head;
		head = tmp;
	}
}

void	Locations::setPath(const std::string &Path)
{
	this->_PathReq = Path;
}

void	Locations::setRoot(const std::string &Root)
{
	this->_Root = Root;
}

void	Locations::addIndex(const std::string &Index)
{
	this->_Index->push_back(Index);
}

void	Locations::setMethod(const std::string &methodName, bool status)
{
	switch (FindMethod(methodName))
	{
		case 0:
			this->_UseGet = status;
			break;
		case 1:
			this->_UsePost = status;
			break;
		case 2:
			this->_UseDelete = status;
	}
}

void	Locations::setBrowsing(bool status)
{
	this->_BrowsDir = status;
}

void	Locations::setRedirection(const std::string &redirectionUrl)
{
	this->_Redirection = redirectionUrl;
	this->_isRedirect = !(redirectionUrl.empty());
}

void	Locations::setNext(Locations *nextRoute)
{
	Locations *tail = this;

	if (!nextRoute)
		return ;
	while (tail->_Next)
		tail = tail->_Next;
	tail->_Next = nextRoute;
	nextRoute->_Prev = tail;
}

const std::string	&Locations::getPath(void) const
{
	return (this->_PathReq);
}

const std::string	&Locations::getRoot(void) const
{
	return (this->_Root);
}

const std::string	&Locations::getRedirection(void) const
{
	return (this->_Redirection);
}

bool	Locations::isRedirection(void) const
{
	return (this->_isRedirect);
}

bool	Locations::useMethod(const std::string &methodName) const
{
	switch (FindMethod(methodName))
	{
		case 0:
			return (this->_UseGet);
		case 1:
			return (this->_UsePost);
		case 2:
			return (this->_UseDelete);
		default:
			return (false);
	}
}

Locations	*Locations::getNext(void)
{
	return (this->_Next);
}

Locations	*Locations::getPrev(void)
{
	return (this->_Prev);
}

bool	Locations::isIndex(const std::string &fileName) const
{
	std::vector<std::string>::iterator it = this->_Index->begin();

	while (it != this->_Index->end())
	{
		if (*it == fileName)
			return (true);
		it++;
	}
	return (false);
}
