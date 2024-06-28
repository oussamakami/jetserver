/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoIndexTools.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:07:55 by okamili           #+#    #+#             */
/*   Updated: 2024/06/28 04:48:15 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

std::vector<std::string>	getDirContent(const std::string &DirPath)
{
	CommandLine		shell;
	std::string		command;

	command = "/bin/ls -1pX ";
	command += DirPath;

	shell.setCommand(command);
	shell.execute();

	return (split(trim(shell.getOutput(), "\n"), "\n"));
}

std::string	generateDirPage(const std::string &DirPath, const std::string &RequestPath)
{
	std::string	result;
	std::string	temp;
	std::vector<std::string> files;

	result = "<!DOCTYPE html><html lang=\"en\"><head><title>webServer v1.0</title></head>";
	result += "<body><center><h1 style=\"font-family: sans-serif;\">List Of Content:</h1><hr>";

	files = getDirContent(DirPath);
	for (int i = 0; i < files.size(); i++)
	{
		temp = "<h3><a href=\"";
		temp += RequestPath;
		temp += files.at(i);
		temp += "\">";
		temp += files.at(i);
		temp += "</a></h3>";
		
		result += temp;
	}
	result += "<hr><h2 style=\"font-family: monospace;\">webServer v1.0</h2></center></body></html>";
	return (result);
}

bool	doesExist(const std::string &path)
{
	CommandLine		shell;
	std::string		command;

	command = "/bin/ls ";
	command += path;
	
	shell.setCommand(command);
	shell.execute();

	return (shell.getStatusCode() == STAT_SUCC);
}

bool	isFolder(const std::string &path)
{
	CommandLine		shell;
	std::string		command;

	command = "/bin/file ";
	command += path;
	
	shell.setCommand(command);
	shell.execute();

	return (trim(split(shell.getOutput(), " ").back(), "\n") == "directory");
}

std::string	getIndexFile(const std::string &DirPath, const Locations *route)
{
	std::vector<std::string>	files;
	std::string					result;

	result = DirPath;
	if (result[result.length()-1] != '/')
		result += '/';
	if (!isFolder(DirPath))
		return (result);

	files = getDirContent(DirPath);

	for (int i = 0; i < files.size(); i++)
	{
		if (files.at(i)[files.at(i).length() - 1] == '/')
			continue;
		if (route->isIndex(files.at(i)))
		{
			result += files.at(i);
			return (result);
		}
	}
	return ("");
}
