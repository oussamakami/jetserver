/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleConnections.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:46:04 by okamili           #+#    #+#             */
/*   Updated: 2024/03/17 06:58:51 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.hpp"

static std::string	getClientIp(sockaddr_in *clientData)
{
	std::string	result;
	char		ipAddrs[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, &(clientData->sin_addr), ipAddrs, INET_ADDRSTRLEN);
	result = ipAddrs;

	return (result);
}

static void	acceptConnections(void)
{
	int							clientFD;
	int							addressSize;
	struct sockaddr_in			address;
	std::vector<int>::const_iterator	it;

	clientFD = -1;
	addressSize = sizeof(address);

	it = global::system->getSockets().begin();

	while (it != global::system->getSockets().end())
	{
		clientFD = accept(*it, (sockaddr *)&address, (socklen_t *)&addressSize);
		global::system->addClient(clientFD);
		it++;
	}
}

static void	prossessReq(void)
{
	
}

// static void prossessRespond(void)
// {
// 	std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
// 	hello += global::servers->getError(500);
// }

void	handleConnections(void)
{
	while(1)
    {
		acceptConnections();
    }
}