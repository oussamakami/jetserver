/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_Get.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 04:56:55 by okamili           #+#    #+#             */
/*   Updated: 2024/06/28 10:32:49 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generateResponse.hpp"

static std::string	extractContentType(ResponseData &Packet, const std::string &output)
{
	int							i;
	std::string					line;
	std::string					result;
	std::vector<std::string>	metaData;
	std::stringstream			ss(output);

	Packet.setMetaData("Content-type", "text/html");
	getline(ss, line);
	metaData = split(line, "; ");

	for (i = 0; i < metaData.size(); i++)
	{
		if (metaData.at(i).find("Content-type") != std::string::npos)
			break;
	}

	if (i < metaData.size())
	{
		metaData = split(metaData.at(i), ": ");
		if (metaData.size() == 2)
			Packet.setMetaData("Content-type", metaData.at(1));
	}

	while (getline(ss, line))
	{
		result += line;
	}
	return (result);
}

void	CGI_Get(ResponseData &Packet, const std::string &filePath)
{
	std::string	command;
	std::string	output;
	CommandLine	shell;

	command = global::system->get_CGI();
	command += " ";
	command += filePath;

	shell.setCommand(command);

	shell.addEnv("GATEWAY_INTERFACE", "CGI/1.1");
	shell.addEnv("REQUEST_METHOD", "GET");
	shell.addEnv("SCRIPT_FILENAME", filePath);
	shell.addEnv("QUERY_STRING", Packet.getRequestPacket()->getMetaData("QueryString"));
	shell.addEnv("SERVER_NAME", Packet.getRequestPacket()->getServer()->getHost());
	shell.addEnv("SERVER_PORT", intToString(Packet.getRequestPacket()->getServer()->getPort()));
	shell.addEnv("SERVER_SOFTWARE", "WebServer/1.0");
	shell.addEnv("REDIRECT_STATUS", "200");

	if (!Packet.getRequestPacket()->getMetaData("User-Agent").empty())
		shell.addEnv("HTTP_USER_AGENT", Packet.getRequestPacket()->getMetaData("User-Agent"));

	shell.execute();
	
	output = extractContentType(Packet, shell.getOutput());

	if (shell.getStatusCode() == STAT_SUCC)
	{
		Packet.setBody(output);
		Packet.setStatusCode(200);
	}
	else
	{
		Packet.setStatusCode(500);
		if (!output.empty())
			Packet.setBody(output);
	}
}