/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParsing.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:25:33 by okamili           #+#    #+#             */
/*   Updated: 2024/05/18 21:16:23 by okamili          ###   ########.fr       */
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

bool	requestParsing(int clientFD, std::map<int, RequestData> &packets)
{
	std::string	clientPacket;
	RequestData	Data(global::system->getClientIP(clientFD));

	clientPacket = readReq(clientFD);
	Data.setSize(clientPacket.length());

	if (Data.getSize() > global::system->getMaxSize())
		return (false);
	
	if (!extractData(clientPacket, Data))
		return (false);

	getServer(Data);

	packets[clientFD] = Data;

	return (true);
}

/**
 * 
 * fix algorithm for detecting the server
 * implement parsing for upload packets
 * fix memory errors in processReq.cpp
 * start working on response
 * 
 * log only in response 
 *  
 * 2024-05-18 14:32:10 [Server] Host: example.com, IP: 192.168.1.1 -> GET /index.html [status 200]
 * 
 * 2024-05-18 14:32:10 [Server] 192.168.1.1 -> GET http://example.com/index.html [status 200]
 * 
 * May 18 14:32:10 [Server] 192.168.1.1 -> GET http://example.com/index.html [status 200]
 */