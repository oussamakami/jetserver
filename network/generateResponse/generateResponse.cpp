/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:02:48 by okamili           #+#    #+#             */
/*   Updated: 2024/06/27 05:56:08 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./generateResponse.hpp"

int	checkRequestFormat(RequestData &data)
{
	std::string	url;
	std::string	Encoding;
	std::string	allowedChars;
	const Locations	*route = data.getServer()->getRoute(url);


	url = data.getPath();
	Encoding = data.getMetaData("Transfer-Encoding");
	allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
	
	if (!data.getServer())
		return (404);
	if (data.getSize() > global::system->getMaxSize())
		return (413);
	if (!Encoding.empty() && Encoding != "chunked")
		return (501);
	if (Encoding.empty() && !data.getSize() && data.getMethod() == "Post")
		return (400);
	if (url.length() > 2048)
		return (414);
	if (!trim(url, allowedChars).empty())
		return (400);
	if (!route->useMethod(data.getMethod()))
		return (405);
	if (data.getProtocol() != "HTTP/1.1")
		return (505);
	return (200);
}

static bool	isRedirection(ResponseData	&Packet)
{
	Locations	*Route;
	std::string	requestPath;

	Route = Packet.getRequestPacket()->getRoute();
	requestPath = Packet.getRequestPacket()->getPath();
	
	if (Route->isRedirection())
		return (Packet.redirect(Route->getRedirection(), Route->isRedirectionHard()));

	if (isFolder(Packet.getRequestPacket()->getFullPath()) && Packet.getRequestPacket()->getMethod() != "POST")
	{
		if (requestPath[requestPath.length() - 1] != '/')
		{
			requestPath += '/';
			return (Packet.redirect(requestPath, true));
		}
	}
	return (false);
}

void	generateResponse(int clientFD, ResponseData &packet)
{
	int	status = 200;

	if (packet.isBusy())
	{
		packet.sendResponse(clientFD);
		return ;
	}
	
	status = checkRequestFormat(*packet.getRequestPacket());
	if (status != 200)
	{
		packet.setStatusCode(status);
		packet.sendResponse(clientFD);
		return ;
	}
	if (isRedirection(packet))
		packet.sendResponse(clientFD);

	if (packet.getRequestPacket()->getMethod() == "GET")
		handleGet(packet);
	else if (packet.getRequestPacket()->getMethod() == "POST")
		handlePost(packet);
	else if (packet.getRequestPacket()->getMethod() == "DELETE")
		packet.setStatusCode(501);
	else
		packet.setStatusCode(405);


	packet.sendResponse(clientFD);
}



/*
4- write description and clean code

5- post in response packet
6- delete in response packet
7- cgi get
8- cgi post
9- cgi delete
10- clean code ready to push

*/