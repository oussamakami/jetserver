/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:52:36 by okamili           #+#    #+#             */
/*   Updated: 2024/05/19 11:08:40 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParsing.hpp"


static Servers	*filterServersByDomain(const std::string &host, std::vector<Servers *> servers)
{
	std::vector<Servers *>::iterator	serversIt;
	
	for (serversIt = servers.begin(); serversIt != servers.end(); serversIt++)
	{
		if ((*serversIt)->hasDomain(host))
			return (*serversIt);
	}
	return (NULL);
}

static Servers *fetchServer(const std::string &host, int port)
{
	std::vector<Servers	*>				result;
	std::vector<Servers *>::iterator	serversIt;

	for (serversIt = global::servers->begin(); serversIt != global::servers->end(); serversIt++)
	{
		if ((*serversIt)->getPort() == port)
			result.push_back(*serversIt);
	}
	return (filterServersByDomain(host, result));
}


void	getServer(RequestData &Data)
{
	std::string		host;
	int				port;
	std::vector<std::string> hostCombinations;

	hostCombinations = split(Data.getMetaData("Host"), ":");

	if (!hostCombinations.size() || hostCombinations.size() > 2)
		return ;
	
	host = hostCombinations.at(0);
	port = 80;

	if (hostCombinations.size() == 2)
		port = StringToInt(hostCombinations.at(1));
	if (host == "localhost")
		host = "127.0.0.1";

	Data.setServer(fetchServer(host, port));
}
