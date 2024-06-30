/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setSockets.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 08:03:54 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 14:03:07 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.hpp"

static std::map<std::string, std::set<uint16_t> > extractInterfaces(void)
{
	std::set<uint16_t>							holder;
	std::map<std::string, std::set<uint16_t> >	result;
	std::vector<Servers *>::iterator			server;
	
	server = global::servers->begin();
	while (server != global::servers->end())
	{
		if (result.find((*server)->getHost()) == result.end())
			result[(*server)->getHost()] = holder;
		result[(*server)->getHost()].insert((*server)->getPort());
		server++;
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

static void	configureSocket(int socketFd)
{
	int	flags;
	int	reuseValue;

	reuseValue = 1;
	flags = fcntl(socketFd, F_GETFL, 0);

	if (flags == -1 || fcntl(socketFd, F_SETFL, flags | O_NONBLOCK) == -1 ||
		setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &reuseValue, sizeof(reuseValue)) == -1)
	{
		notify(std::cerr, "%EFailed to perform operations on the socket.");
		close(socketFd);
		terminate(3);
	}
}

static void	bindSocket(int socketFd, const sockaddr_in &address)
{
	if (bind(socketFd, (struct sockaddr *) &address, sizeof(address)) == -1)
	{
		notify(std::cerr, "%EBinding the socket failed.");
		close(socketFd);
		terminate(3);
	}
}

static int	createSocket(const std::string &Host, uint16_t Port)
{
	int					socketFd;
	struct sockaddr_in	addrs;

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
	configureSocket(socketFd);
	bindSocket(socketFd, addrs);
	return (socketFd);
}

static void startListening(int socketFd, int queueLimit)
{
	if (listen(socketFd, queueLimit) == -1)
	{
		notify(std::cerr, "%EUnable to listen for connections on the socket.");
		close(socketFd);
		terminate(3);
	}
}

void	setSockets(void)
{
	int														socketFd;
	std::map<std::string, std::set<uint16_t> >				interfaces;
	std::map<std::string, std::set<uint16_t> >::iterator	it;

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