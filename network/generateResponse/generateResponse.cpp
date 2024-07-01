/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:02:48 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 19:49:48 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./generateResponse.hpp"

int	checkRequestFormat(RequestData &data)
{
	std::string	url;
	std::string	Encoding;
	std::string	allowedChars;
	const Locations	*route;


	url = data.getPath();
	route = data.getServer()->getRoute(url);
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
	if (data.getMethod() == "Post" && !data.getSize() && !data.getBody().empty())
		return (411);
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

	if (isFolder(Packet.getRequestPacket()->getFullPath()) && Packet.getRequestPacket()->getMethod() == "GET")
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
	{
		packet.sendResponse(clientFD);
		return ;
	}

	if (packet.getRequestPacket()->getMethod() == "GET")
		handleGet(packet);
	else if (packet.getRequestPacket()->getMethod() == "POST")
		handlePost(packet);
	else if (packet.getRequestPacket()->getMethod() == "DELETE")
		handleDelete(packet);
	else
		packet.setStatusCode(501);


	packet.sendResponse(clientFD);
}