/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractData.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:38:55 by okamili           #+#    #+#             */
/*   Updated: 2024/06/28 08:24:02 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParsing.hpp"

static std::string	correctString(const std::string &str)
{
	int length = 0;
	while (str[length])
		length++;
	if (str.length() != length)
		return (str.substr(0, length));
	return (str);
}

static bool	extractRequest(const std::string &line, RequestData &Data)
{
	std::vector<std::string> splittedLine;
	
	splittedLine = split(line, " ");

	if (splittedLine.size() != 3)
		return (false);

	Data.setMethod(correctString(splittedLine[0]));
	Data.setPath(correctString(splittedLine[1]));
	Data.setProtocol(correctString(splittedLine[2]));

	return (true);
}

static bool	extractMetaData(const std::string &line, RequestData &Data)
{
	std::vector<std::string> splittedLine;
	std::vector<std::string> temp;

	splittedLine = split(line, ": ");

	if (splittedLine.size() != 2)
	{
		splittedLine = split(line, "=");
		if (splittedLine.size() != 2)
			return (false);
	}
	
	temp = split(splittedLine[1], "; ");
	if (temp.size() != 1)
	{
		Data.addMetaData(correctString(splittedLine[0]), correctString(splittedLine[1]));
		extractMetaData(temp[1], Data);
	}
	else
		Data.addMetaData(correctString(splittedLine[0]), correctString(splittedLine[1]));
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
