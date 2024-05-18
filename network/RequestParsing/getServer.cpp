/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:52:36 by okamili           #+#    #+#             */
/*   Updated: 2024/05/18 15:44:46 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParsing.hpp"


static void	getServerFromDomain(RequestData &Data, std::vector<Servers *> servers)
{
	std::string							domainName;
	std::vector<Servers *>::iterator	serversIt;

	domainName = Data.getMetaData("Host");

	if (split(domainName, ":").size() == 2)
		domainName = split(domainName, ":")[0];
	if (domainName == "localhost")
		domainName = "127.0.0.1";
	
	for (serversIt = servers.begin(); serversIt != servers.end(); serversIt++)
	{
		if ((*serversIt)->hasDomain(domainName))
		{
			Data.setServer(*serversIt);
			return ;
		}
	}
}

static void getServerFromIP(RequestData &Data)
{
	int									port;
	std::vector<Servers	*>				result;
	std::vector<Servers *>::iterator	serversIt;

	port = StringToInt(split(Data.getMetaData("Host"), ":").at(1));

	for (serversIt = global::servers->begin(); serversIt != global::servers->end(); serversIt++)
	{
		if ((*serversIt)->getPort() == port)
			result.push_back(*serversIt);
	}

	if (result.size() > 1)
	{
		getServerFromDomain(Data, result);
		return ;
	}
	else if (!result.empty())
		Data.setServer(result[0]);
}

void	getServer(RequestData &Data)
{
	if (split(Data.getMetaData("Host"), ":").size() == 2)
		getServerFromIP(Data);
	else
		getServerFromDomain(Data, *global::servers);
}
