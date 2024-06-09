/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:02:48 by okamili           #+#    #+#             */
/*   Updated: 2024/06/09 14:55:32 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../network.hpp"

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
	return (200);
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
	// ResponseData	packet(data);

	handleGet(packet);
	// packet.setStatusCode(200);
	// packet.setBody(packet.getRequestPacket()->getServer()->getError(512));
	packet.sendResponse(clientFD);
}



/*
2- handle get method, response packet


3- handle upload in request
4- write description and clean code

5- post in response packet
6- delete in response packet
7- cgi get
8- cgi post
9- cgi delete
10- clean code ready to push

*/