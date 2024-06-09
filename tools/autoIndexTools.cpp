/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoIndexTools.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:07:55 by okamili           #+#    #+#             */
/*   Updated: 2024/06/09 09:09:12 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

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
