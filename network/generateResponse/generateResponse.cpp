/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:02:48 by okamili           #+#    #+#             */
/*   Updated: 2024/06/08 13:51:13 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../network.hpp"

std::vector<std::string>	getDirContent(const std::string &path)
{
	std::string	cmd;
	std::string	rawData;
	std::vector<std::string> result;

	cmd = "/bin/ls|-1pX|";
	cmd += path;

	executeCMD(cmd, rawData);

	rawData = trim(rawData, "\n");
	result = split(rawData, "\n");

	return (result);
}

std::string	generateDirPage(const std::string &path)
{
	std::string	result;
	std::string	temp;
	std::vector<std::string> files;

	result = "<!DOCTYPE html><html lang=\"en\"><head><title>webServer v1.0</title></head>";
	result += "<body><center><h1 style=\"font-family: sans-serif;\">List Of Content:</h1><hr>";

	files = getDirContent(path);
	for (int i = 0; i < files.size(); i++)
	{
		temp = "<h3><a href=\"";
		temp += path;
		temp += files.at(i);
		temp += "\">";
		temp += files.at(i);
		temp += "</a></h3>";
		
		result += temp;
	}
	result += "<hr><h2 style=\"font-family: monospace;\">webServer v1.0</h2></center></body></html>";
	return (result);
}

bool	isFolder(const std::string &path)
{
	std::string	cmd;
	std::string	rawData;
	
	cmd = "/bin/file|";
	cmd += path;

	executeCMD(cmd, rawData);

	return (trim(split(rawData, " ").back(), "\n") == "directory");
}

int	checkRequestFormat(RequestData &data)
{
	std::string	url;
	std::string	Encoding;
	std::string	allowedChars;
	const Locations	*route = data.getServer()->getRoute(url);


	url = data.getPath();
	Encoding = data.getMetaData("Transfer-Encoding");
	allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";

	if (data.getSize() > global::system->getMaxSize())
		return (413);
	if (!Encoding.empty() && Encoding != "chunked")
		return (501);
	if (Encoding.empty() && !data.getSize() && data.getMethod() == "Post")
		return (400);
	if (url.length() > 2048)
		return (414);
	if (!trim(url, allowedChars).empty())
		return (400);
	if (!route->useMethod(data.getMethod()))
		return (405);
	return (200);
}

//return path to file, if cant get file return empty to indicate need folder listing


std::string	getIndexFile(std::string path, const Locations *route)
{
	std::vector<std::string> files;

	if (!isFolder(path))
		return (path);
	
	files = getDirContent(path);
	
	for (int i = 0; i < files.size(); i++)
	{
		if (files.at(i)[files.at(i).length() - 1] == '/')
			continue;
		if (route->isIndex(files.at(i)))
		{
			path += files.at(i);
			return (path);
		}
	}
	return ("");
}


// void	generateResponse(int clientFD, RequestData &data)
// {
// 	ResponseData	response(data);
// 	int status = 200;

// 	status = checkRequestFormat(data);
// 	if (status != 200)
// 	{
// 		response.setStatusCode(status);
// 		//sending
// 		return;
// 	}
	
// }






















void	generateResponse(int clientFD, RequestData &data)
{
	ResponseData	packet(data);

	packet.setStatusCode(200);
	packet.setBody(data.getServer()->getError(512));
	packet.sendResponse(clientFD);
	while (packet.isBusy())
	{
		packet.sendResponse(clientFD);
	}
	// std::string response = "HTTP/1.1 200 OK\r\n"
    //                    "Content-Type: text/html\r\n"
    //                    "Content-Length: 225\r\n\r\n";

	// if (data.getServer())
	// 	response += global::servers->at(0)->getError(500);
	// else
	// 	response += global::servers->at(0)->getError(404);

	// notify(std::cout, "the host: %s", data.getMetaData("Host").c_str());
	// if (data.getServer())
	// 	notify(std::cout, "server found: %s:%d", data.getServer()->getHost().c_str(), data.getServer()->getPort());
	// write(clientFD, response.c_str(), response.length());
}
