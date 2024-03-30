/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseReq.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:25:33 by okamili           #+#    #+#             */
/*   Updated: 2024/03/29 16:06:00 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.hpp"

std::string	readReq(int clientFD)
{
	int			bytesReceived;
	int			maxBufferSize = global::system->getMaxSize() + 1000;
	char		buffer[maxBufferSize];
	std::string	packet;
	packet = "";
	bytesReceived = recv(clientFD, buffer, maxBufferSize, 0);
	if (bytesReceived < 0)
		return ("");
	packet.append(buffer, bytesReceived);
	return (packet);
}

bool	parseReq(int clientFD, std::map<int, RequestData> &packets)
{
	std::string	clientPacket;
	RequestData	Data(global::system->getClientIP(clientFD));

	clientPacket = readReq(clientFD);
	Data.setSize(clientPacket.length());
	if (Data.getSize() > global::system->getMaxSize())
		return (false);
	packets[clientFD] = Data;
	return (true);
}
