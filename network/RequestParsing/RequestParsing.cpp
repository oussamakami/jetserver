/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParsing.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:25:33 by okamili           #+#    #+#             */
/*   Updated: 2024/06/10 14:28:37 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParsing.hpp"

static std::string	readReq(int clientFD)
{
	int			bytesReceived;
	int			maxBufferSize = 1024;
	char		buffer[maxBufferSize];
	std::string	httpPacket = "";

	while (true)
	{
		bytesReceived = recv(clientFD, buffer, maxBufferSize - 1, 0);
		if (bytesReceived > 0)
		{
			buffer[bytesReceived] = '\0';
			httpPacket += buffer;
			if (httpPacket.find("\r\n\r\n") != std::string::npos)
				break;
		}
		else
			break;
	}

	return (httpPacket);
}

bool	requestParsing(int clientFD, RequestData &packetData)
{
	std::string	clientPacket;

	clientPacket = readReq(clientFD);
	std::cout << clientPacket << "\n";
	if (!packetData.getClientIP().empty())
	{
		//parse just body
		return (true);
	}
	packetData.setClientIP(global::system->getClientIP(clientFD));
	packetData.setSize(clientPacket.length());
	if (!extractData(clientPacket, packetData))
		return (false);
	getServer(packetData);
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