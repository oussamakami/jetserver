/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setSockets.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 08:03:54 by okamili           #+#    #+#             */
/*   Updated: 2024/03/17 03:26:50 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.hpp"

static std::map<std::string, std::set<uint16_t> > extractInterfaces(void)
{
	std::set<uint16_t>							holder;
	std::map<std::string, std::set<uint16_t> >	result;

	for (Servers *head = global::servers; head; head = head->getNext())
	{
		if (result.find(head->getHost()) == result.end())
			result[head->getHost()] = holder;
		result[head->getHost()].insert(head->getPort());
	}
	return (result);
}

static void	removeSocketPorts(std::map<std::string, std::set<uint16_t> > &interfaces, uint16_t port)
{
	std::map<std::string, std::set<uint16_t> >::iterator	it;

	for (it = interfaces.begin(); it != interfaces.end(); it++)
	{
		if (it->first == "0.0.0.0")
			continue;
		it->second.erase(port);
	}
}

static std::map<std::string, std::set<uint16_t> > extractBindableInterfaces(void)
{
	std::set<uint16_t>::iterator				it;
	std::map<std::string, std::set<uint16_t> >	interfaces;

	interfaces = extractInterfaces();

	if (interfaces.find("0.0.0.0") == interfaces.end())
		return (interfaces);

	for (it = interfaces["0.0.0.0"].begin(); it != interfaces["0.0.0.0"].end(); it++)
		removeSocketPorts(interfaces, *it);

	return (interfaces);
}

static int	createSocket(const std::string &Host, uint16_t Port)
{
	struct sockaddr_in	addrs;
	int					flags;
	int					socketFd;
	int					reuseValue;

	reuseValue = 1;
	addrs.sin_family = AF_INET;
	addrs.sin_port = htons(Port);
	if (inet_pton(AF_INET, Host.c_str(), &addrs.sin_addr) < 1)
	{
		notify(std::cerr, "%EThe host IP address is invalid or unsupported.");
		terminate(3);
	}

	socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFd == -1)
	{
		notify(std::cerr, "%EFailed to create the socket endpoint.");
		close(socketFd);
		terminate(3);
	}

	setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &reuseValue, sizeof(reuseValue));

	flags = fcntl(socketFd, F_GETFL, 0);
	
	if (flags == -1 || fcntl(socketFd, F_SETFL, flags | O_NONBLOCK) == -1)
	{
		notify(std::cerr, "%EFailed to perform operations on the socket.");
		close(socketFd);
		terminate(3);
	}

	if (bind(socketFd, (struct sockaddr *) &addrs, sizeof(addrs)) == -1)
	{
		notify(std::cerr, "%EBinding the socket failed.");
		close(socketFd);
		terminate(3);
	}
	return (socketFd);
}

static void startListening(int socketFd, int queueLimit)
{
	if (listen(socketFd, 100) == -1)
	{
		notify(std::cerr, "%EUnable to listen for connections on the socket.");
		close(socketFd);
		terminate(3);
	}
}

void	setSockets(void)
{
	int														socketFd;
	std::map<std::string, std::set<uint16_t> >::iterator	it;
	std::map<std::string, std::set<uint16_t> >				interfaces;

	interfaces = extractBindableInterfaces();
	it = interfaces.begin();

	while (it != interfaces.end())
	{
		if (!it->second.empty())
		{
			socketFd = createSocket(it->first.c_str(), *(it->second.begin()));
			startListening(socketFd, 50);

			notify(std::cout, "%IListening on Socket %s:%d.",
				it->first.c_str(), *(it->second.begin()));

			it->second.erase(it->second.begin());
			global::system->addSocket(socketFd);
		}
		else
			it++;
	}
}
