/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParsing.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:25:33 by okamili           #+#    #+#             */
/*   Updated: 2024/07/01 12:27:48 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParsing.hpp"

static std::string	readReq(int clientFD)
{
	int			bytesReceived;
	int			maxBufferSize = 1048576;
	char		buffer[maxBufferSize];
	std::string	httpPacket;

	bytesReceived = recv(clientFD, buffer, maxBufferSize, 0);

	if (bytesReceived != -1)
		httpPacket.append(buffer, bytesReceived);

	return (httpPacket);
}

static void	extractBody(const std::string &packet, RequestData &data)
{
	std::string	boundary = data.getMetaData("boundary");
	size_t			startpos = 0;

	if (boundary.empty())
	{
		startpos = packet.find("\r\n\r\n");
		if (startpos != std::string::npos)
			data.appendBody(packet.substr(startpos + 4));
		return;
	}
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