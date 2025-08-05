/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePost.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 00:57:35 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 12:18:29 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./generateResponse.hpp"

#define STAT_CREAT	1

static std::string	correctString(const std::string &str)
{
	size_t length = 0;
	while (str[length])
		length++;
	if (str.length() != length)
		return (str.substr(0, length));
	return (str);
}

static std::string	extractHead(const std::string &boundary, std::string &body)
{
	size_t		startPos;
	size_t		endPos;
	std::string	startBoundary;
	std::string result;

	startBoundary = "--" + boundary;
	startPos = body.find(startBoundary);

	if (startPos == std::string::npos)
		return ("");

	startPos += startBoundary.length();
	endPos = body.find("\r\n\r\n", startPos);

	if (endPos == std::string::npos)
		return ("");
	result = body.substr(startPos, endPos - startPos);
	body = body.substr(result.length() + startBoundary.length() + 4);
	if (result.find("\r\n") != std::string::npos)
		result.erase(result.find("\r\n"), 2);
	return (result);
}

static std::string	extractBody(const std::string &boundary, std::string &body)
{
	size_t		endPos;
	std::string	endBoundary;
	std::string	result;

	endBoundary = "--" + boundary;
	endPos = body.find(endBoundary);

	if (endPos == std::string::npos)
		return ("");
	
	result = body.substr(0, endPos);
	body = body.substr(result.length());

	endBoundary += "--";
	endPos = body.find(endBoundary);
	if (endPos != std::string::npos && !endPos)
		body = "";
	return (result.substr(0, result.length() - 2));
}

static std::map<std::string, std::string>	parseHead(const std::string &head)
{
	std::stringstream					headMetaData;
	std::string							line;
	std::vector<std::string>			list;
	std::vector<std::string>			temp;
	std::map<std::string, std::string>	result;

	headMetaData << head;
	while (getline(headMetaData, line))
	{
		list = split(line, "; ");
		for (size_t i = 0; i < list.size(); i++)
		{
			temp = split(list.at(i), ": ");
			if (temp.size() != 2)
				temp = split(list.at(i), "=");
			if (temp.size() != 2)
				continue;
			result[correctString(temp[0])] = trim(correctString(temp[1]), "\"");
		}
	}
	return (result);
}
static	bool	SaveFile(const std::string &fullPath, const std::string fileName, const std::string &body)
{
	size_t						fileCount = 0;
	std::string					customPath = fullPath + "/";
	std::string					customName = fileName;
	std::fstream				fileData;
	std::vector<std::string>	dirContent = getDirContent(fullPath);

	for (size_t i = 0; i < customName.length(); i++)
	{
		if (customName[i] == ' ')
			customName[i] = '_';
	}
	
	for (size_t i = 0; i < dirContent.size(); i++)
	{
		if (customName == dirContent.at(i))
		{
			customName = "(" + intToString(++fileCount) + ")-" + fileName;
			i = -1;
		}
	}
	customPath += customName;
	fileData.open(customPath.c_str(), std::ios::out | std::ios::binary);
	if (!fileData.is_open())
		return (false);
	fileData << body;
	fileData.close();
	return (true);
}

static int	handleBodySection(const std::string &fullPath, const std::string &boundary, std::string &packetBody)
{
	std::fstream file;
	std::map<std::string, std::string>	list;

	list = parseHead(extractHead(boundary, packetBody));
	list["bodyData"] = extractBody(boundary, packetBody);
	
	if (list.find("filename") != list.end() && !list.at("bodyData").empty())
	{
		if (SaveFile(fullPath, list.at("filename"), list.at("bodyData")))
			return (STAT_CREAT);
		return (STAT_ERR);
	}
	return (STAT_SUCC);
}

static int	handleBody(ResponseData &Packet)
{
	int			sectionCode;
	int			statusCode;
	std::string	fullPath;
	std::string	boundary;
	std::string	bodyData;
	std::string	packetResponse;

	sectionCode = 0;
	statusCode = 200;
	fullPath = Packet.getRequestPacket()->getFullPath();
	boundary = Packet.getRequestPacket()->getMetaData("boundary");
	bodyData = Packet.getRequestPacket()->getBody();

	while (!bodyData.empty())
	{
		sectionCode = handleBodySection(fullPath, boundary, bodyData);
		if (sectionCode == STAT_CREAT && statusCode < 201)
			statusCode = 201;
		if (sectionCode == STAT_ERR)
			statusCode = 500;
	}

	packetResponse = "<!DOCTYPE html><html lang=\"en\"><head><title>JetServer v1.0</title>";
	packetResponse += "</head><body><center><h1 style=\"font-family: sans-serif;\">File(s) ";
	packetResponse += "uploaded successfully</h1><a href=\"/\">Go to homepage</a><hr><h3 ";
	packetResponse += "style=\"font-family: monospace;\">JetServer v1.0</h3></center></body></html>";
	
	if (statusCode == 201)
		Packet.setBody(packetResponse);
	Packet.setStatusCode(statusCode);
	return (statusCode);
}


bool	handlePost(ResponseData &Packet)
{
	std::string	indexFile;
	std::string	fullPath;
	Locations	*route;

	fullPath = Packet.getRequestPacket()->getFullPath();
	route = Packet.getRequestPacket()->getRoute();
	
	if (!route->useMethod("POST"))
	{
		Packet.setStatusCode(405);
		return (true);
	}
	if (!doesExist(fullPath))
	{
		Packet.setStatusCode(404);
		return (true);
	}
	if (isFolder(fullPath))
	{
		indexFile = getIndexFile(fullPath, Packet.getRequestPacket()->getRoute());
		if (!indexFile.empty())
		{
			if (isCGI(indexFile))
			{
				CGI_Post(Packet, indexFile);
				return (true);
			}
		}
		if (handleBody(Packet) != 500)
			Packet.readFile(indexFile);
		return (true);
	}
	if (!isFolder(fullPath))
	{
		if (isCGI(fullPath))
		{
			CGI_Post(Packet, fullPath);
			return (true);
		}
	}
	Packet.setStatusCode(403);
	return (true);
}