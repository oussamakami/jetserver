/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractData.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:38:55 by okamili           #+#    #+#             */
/*   Updated: 2024/06/10 22:59:54 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParsing.hpp"

static bool	extractRequest(const std::string &line, RequestData &Data)
{
	std::vector<std::string> splittedLine;
	
	splittedLine = split(line, " ");

	if (splittedLine.size() != 3)
		return (false);

	Data.setMethod(splittedLine[0]);
	Data.setPath(splittedLine[1]);
	Data.setProtocol(splittedLine[2]);

	return (true);
}

static bool	extractMetaData(const std::string &line, RequestData &Data)
{
	std::vector<std::string> splittedLine;

	splittedLine = split(line, ": ");

	if (splittedLine.size() != 2)
		return (false);
	
	if (splittedLine[0] == "Content-Type")
	{
		std::vector<std::string> temp = split(splittedLine[1], "; ");
		Data.addMetaData(splittedLine[0], temp[0]);
		temp = split(temp[1], "=");
		Data.addMetaData(temp[0], temp[1].substr(0, temp[1].length() - 1));
	}
	else
		Data.addMetaData(splittedLine[0], splittedLine[1]);

	return (true);
}

bool	extractData(const std::string &packet, RequestData &Data)
{
	std::string			line;
	std::stringstream	packetData(packet);

	if (!getline(packetData, line) || !extractRequest(line, Data))
		return (false);

	line = "";

	for (getline(packetData, line); line.length() > 1; getline(packetData, line))
	{
		if (!extractMetaData(line, Data))
			return (false);	
		line = "";
	}

	return (true);
}
