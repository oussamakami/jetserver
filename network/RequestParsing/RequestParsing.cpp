/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParsing.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:25:33 by okamili           #+#    #+#             */
/*   Updated: 2024/06/28 05:33:26 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParsing.hpp"

static std::string	readReq(int clientFD)
{
	int			bytesReceived;
	int			maxBufferSize = 1024;
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
	int			startpos = 0;

	if (boundary.empty())
		return;
	startpos = packet.find(boundary, packet.find(boundary) + 1);

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

/**
 * 
 * implement parsing for upload packets
 * 
 * log only in response 
 *  
 * 2024-05-18 14:32:10 [Server] Host: example.com, IP: 192.168.1.1 -> GET /index.html [status 200]
 * 
 * 2024-05-18 14:32:10 [Server] 192.168.1.1 -> GET http://example.com/index.html [status 200]
 * 
 * May 18 14:32:10 [Server] 192.168.1.1 -> GET http://example.com/index.html [status 200]
 */