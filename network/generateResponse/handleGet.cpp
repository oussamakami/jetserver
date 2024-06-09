/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleGet.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:13:00 by okamili           #+#    #+#             */
/*   Updated: 2024/06/09 16:51:53 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../network.hpp"

static bool	isRedirection(ResponseData	&Packet)
{
	Locations	*Route;
	std::string	requestPath;

	Route = Packet.getRequestPacket()->getRoute();
	requestPath = Packet.getRequestPacket()->getPath();
	
	if (Route->isRedirection())
		return (Packet.redirect(Route->getRedirection(), Route->isRedirectionHard()));

	if (isFolder(Packet.getRequestPacket()->getFullPath()))
	{
		if (requestPath[requestPath.length() - 1] != '/')
		{
			requestPath += '/';
			return (Packet.redirect(requestPath, true));
		}
	}
	return (false);
}

static bool	handleAutoIndex(ResponseData &Packet)
{
	std::string	RequestPath;
	std::string	FolderPath;
	Locations	*Route;

	RequestPath = Packet.getRequestPacket()->getPath();
	FolderPath = Packet.getRequestPacket()->getFullPath();
	Route = Packet.getRequestPacket()->getRoute();

	if (FolderPath.empty() || !Route)
		return (false);
	if (!Route->autoIndex())
	{
		Packet.setStatusCode(404);
		return (true);
	}
	Packet.setStatusCode(200);
	Packet.setBody(generateDirPage(FolderPath, RequestPath));
	return (true);
}

bool	handleGet(ResponseData &Packet)
{
	std::string	RequestPath;
	std::string	FilePath;
	std::string	Temp;

	RequestPath = Packet.getRequestPacket()->getPath();
	FilePath = Packet.getRequestPacket()->getFullPath();
	if (isRedirection(Packet))
		return (true);
	if (isFolder(FilePath))
	{
		Temp = getIndexFile(FilePath, RequestPath, Packet.getRequestPacket()->getRoute());
		if (Temp.empty())
			return (handleAutoIndex(Packet));
		FilePath = Temp;
	}
	if (!doesExist(FilePath))
	{
		Packet.setStatusCode(404);
		return (true);
	}

	//handling file reading
	Packet.setStatusCode(200);
	Packet.setMetaData("ContentType", "text/plain");
	Packet.setBody("holla babybi");
	return (true);
}
