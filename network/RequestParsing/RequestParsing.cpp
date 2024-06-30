/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParsing.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:25:33 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 14:09:43 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParsing.hpp"

static std::string	readReq(int clientFD)
{
	int			bytesReceived;
	int			maxBufferSize = 8192;
	char		buffer[maxBufferSize];
	std::string	httpPacket;

	while (true)
	{
		bytesReceived = recv(clientFD, buffer, maxBufferSize, 0);
		httpPacket.append(buffer, bytesReceived);
		if (httpPacket.find("\r\n\r\n") != std::string::npos)
			break;
		if (bytesReceived < maxBufferSize)
			break;
	}

	return (httpPacket);
}

static void	extractBody(const std::string &packet, RequestData &data)
{
	std::string	boundary = data.getMetaData("boundary");
	size_t			startpos = 0;

	if (boundary.empty())
		return;
	startpos = packet.find(boundary, packet.find(boundary) + 1);

	if (startpos == std::string::npos)
		return ;

	data.appendBody("--");
	data.appendBody(packet.substr(startpos));
}

bool	requestParsing(int clientFD, RequestData &packetData)
{
	std::string	clientPacket;

	clientPacket = readReq(clientFD);
	if (!packetData.getClientIP().empty())
	{
		packetData.appendBody(clientPacket);
		return (true);
	}
	packetData.setClientIP(global::system->getClientIP(clientFD));
	if (!extractData(clientPacket, packetData))
		return (false);
	packetData.setSize(StringToInt(packetData.getMetaData("Content-Length")));
	getServer(packetData);
	extractBody(clientPacket, packetData);
	return (true);
}