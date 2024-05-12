/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processReq.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:10:32 by okamili           #+#    #+#             */
/*   Updated: 2024/05/12 06:34:06 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.hpp"

static pollfd	*closeConnection(int clientFD)
{
	global::system->deleteClient(clientFD);
	return (&(global::system->getNetworkFDs()[0]));
}

static std::string	getClientIp(sockaddr_in *clientData)
{
	std::string	result;
	char		ipAddrs[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, &(clientData->sin_addr), ipAddrs, INET_ADDRSTRLEN);
	result = ipAddrs;

	return (result);
}

static bool	extractReqFD(int fd)
{
	int					clientFD;
	int					addressSize;
	struct sockaddr_in	address;

	addressSize = sizeof(address);

	if (global::system->getSockets().find(fd) == global::system->getSockets().end())
		return (false);

	clientFD = accept(fd, (sockaddr *)&address, (socklen_t *)&addressSize);
	if (clientFD == -1)
	{
		notify(std::cerr, "%EFailed to accept client requests.");
		terminate(3);
	}
	global::system->addClient(clientFD, getClientIp(&address));
	return (true);
}

static void	manageClients(pollfd *clientsFDs, std::string &msg)
{
	static std::map<int, RequestData>	packetsData;

	for (int index = 0; index < global::system->getNetworkFDs().size(); index++)
	{
		if (clientsFDs[index].revents & POLLIN)
		{
			if (extractReqFD(clientsFDs[index].fd))
			{
				clientsFDs = &(global::system->getNetworkFDs()[0]);
				continue;
			}
			if (!parseReq(clientsFDs[index].fd, packetsData))
			{
				clientsFDs = closeConnection(clientsFDs[index].fd);
				index--;
				continue;
			}
			clientsFDs[index].events = POLLOUT | POLLERR;
		}
		else if (clientsFDs[index].revents & POLLOUT)
		{
			//sendResponse()
			write(clientsFDs[index].fd, msg.c_str(), msg.length());
			clientsFDs[index].events = POLLIN | POLLERR;
		}
		if (clientsFDs[index].revents & POLLERR)
		{
			clientsFDs = closeConnection(clientsFDs[index].fd);
			index--;
		}
	}
}

void	prossessReq(void)
{
	struct pollfd	*clientsFDs;
	
	std::string response = "HTTP/1.1 200 OK\r\n"
                       "Content-Type: text/html\r\n"
                       "Content-Length: 225\r\n\r\n";
	response += global::servers->at(0)->getError(500);
	
	clientsFDs = &(global::system->getNetworkFDs()[0]);

	if (poll(clientsFDs, global::system->getNetworkFDs().size(), 5) == -1)
	{
		notify(std::cerr, "%EPolling the file descriptors failed.");
		terminate(3);
	}

	manageClients(clientsFDs, response);
}
