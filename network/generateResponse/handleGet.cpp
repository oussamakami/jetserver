/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleGet.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:13:00 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 14:16:32 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./generateResponse.hpp"

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
		Packet.setStatusCode(403);
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

	FilePath = Packet.getRequestPacket()->getFullPath();
	if (isFolder(FilePath))
	{
		Temp = getIndexFile(FilePath, Packet.getRequestPacket()->getRoute());
		if (Temp.empty())
			return (handleAutoIndex(Packet));
		FilePath = Temp;
	}
	if (!doesExist(FilePath))
	{
		Packet.setStatusCode(404);
		return (true);
	}
	if (isCGI(FilePath))
	{
		CGI_Get(Packet, FilePath);
		return (true);
	}
	Packet.setStatusCode(200);
	Packet.readFile(FilePath);
	return (true);
}