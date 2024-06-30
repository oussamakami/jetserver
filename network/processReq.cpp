/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processReq.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:10:32 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 14:08:29 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.hpp"

static void	closeConnection(int clientFD, std::map<int, RequestData*> &requests,
	std::map<int, ResponseData*> &responses)
{
	if (requests.find(clientFD) != requests.end())
	{
		delete requests.find(clientFD)->second;
		requests.erase(requests.find(clientFD));
	}
	if (responses.find(clientFD) != responses.end())
	{
		delete responses.find(clientFD)->second;
		responses.erase(responses.find(clientFD));
	}
	global::system->deleteClient(clientFD);
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

static void	manageClients(pollfd *clientsFDs)
{
	static std::map<int, RequestData*>	RequestPackets;
	static std::map<int, ResponseData*>	ResponsePackets;

	for (size_t index = 0; index < global::system->getNetworkFDs().size(); index++)
	{
		if (clientsFDs[index].revents & POLLIN)
		{
			if (extractReqFD(clientsFDs[index].fd))
				break;
			else
			{
				if (RequestPackets.find(clientsFDs[index].fd) == RequestPackets.end())
					RequestPackets[clientsFDs[index].fd] = new RequestData();
				if (!requestParsing(clientsFDs[index].fd, *RequestPackets[clientsFDs[index].fd]))
				{
					closeConnection(clientsFDs[index].fd, RequestPackets, ResponsePackets);
					break;
				}
			}
			clientsFDs[index].events = POLLIN | POLLOUT | POLLERR;
		}
		else if (clientsFDs[index].revents & POLLOUT)
		{
			if (!RequestPackets[clientsFDs[index].fd]->getBody().empty())
			{
				if (RequestPackets[clientsFDs[index].fd]->getBody().length() < RequestPackets[clientsFDs[index].fd]->getSize())
					continue;
			}
			if (ResponsePackets.find(clientsFDs[index].fd) == ResponsePackets.end())
			{
				ResponsePackets[clientsFDs[index].fd] = new ResponseData();
				ResponsePackets[clientsFDs[index].fd]->setRequestPacket(*RequestPackets[clientsFDs[index].fd]);
			}
			generateResponse(clientsFDs[index].fd, *ResponsePackets[clientsFDs[index].fd]);
			if (!ResponsePackets[clientsFDs[index].fd]->isBusy())
			{
				closeConnection(clientsFDs[index].fd, RequestPackets, ResponsePackets);
				break;
			}
			clientsFDs[index].events = POLLOUT | POLLERR;
		}
		if (clientsFDs[index].revents & POLLERR)
		{
			closeConnection(clientsFDs[index].fd, RequestPackets, ResponsePackets);
			break;
		}
	}
}

void	prossessReq(void)
{
	struct pollfd	*clientsFDs;
	
	clientsFDs = &(global::system->getNetworkFDs().at(0));

	if (poll(clientsFDs, global::system->getNetworkFDs().size(), 5) == -1)
	{
		notify(std::cerr, "%EPolling the file descriptors failed.");
		terminate(3);
	}

	manageClients(clientsFDs);
}