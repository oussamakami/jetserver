/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_Delete.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:54:39 by okamili           #+#    #+#             */
/*   Updated: 2024/07/04 20:53:29 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generateResponse.hpp"

static std::string	extractContentType(ResponseData &Packet, const std::string &output)
{
	std::string					line;
	std::string					result;
	std::vector<std::string>	metaData;
	std::stringstream			ss(output);
	bool						hasHeader = false;

	Packet.setMetaData("Content-type", "text/html");

	for (int i = 0; getline(ss, line); i++)
	{
		if (i > 3 && !hasHeader)
			return (output);
		if (i < 4 && !hasHeader)
		{
			if (line.length() == 1)
				hasHeader = true;
			continue;
		}
		result += line;
	}

	return (result);
}

void	CGI_Delete(ResponseData &Packet, const std::string &filePath)
{
	std::string	command;
	std::string	output;
	CommandLine	shell;

	command = global::system->get_CGI();
	command += " ";
	command += filePath;

	shell.setCommand(command);

	shell.addEnv("SERVER_PROTOCOL", Packet.getRequestPacket()->getProtocol());
	shell.addEnv("GATEWAY_INTERFACE", "CGI/1.1");
	shell.addEnv("REQUEST_METHOD", "DELETE");
	shell.addEnv("SCRIPT_FILENAME", filePath);
	shell.addEnv("QUERY_STRING", Packet.getRequestPacket()->getMetaData("QueryString"));
	shell.addEnv("REMOTE_ADDR", Packet.getRequestPacket()->getClientIP());
	shell.addEnv("SERVER_NAME", Packet.getRequestPacket()->getServer()->getHost());
	shell.addEnv("SERVER_PORT", intToString(Packet.getRequestPacket()->getServer()->getPort()));
	shell.addEnv("CONTENT_TYPE", Packet.getRequestPacket()->getMetaData("Content-Type"));
	shell.addEnv("CONTENT_LENGTH", Packet.getRequestPacket()->getMetaData("Content-Length"));
	shell.addEnv("SERVER_SOFTWARE", "WebServer/1.0");
	shell.addEnv("REDIRECT_STATUS", "200");

	if (!Packet.getRequestPacket()->getMetaData("User-Agent").empty())
		shell.addEnv("HTTP_USER_AGENT", Packet.getRequestPacket()->getMetaData("User-Agent"));
	shell.setInput(Packet.getRequestPacket()->getBody());
	shell.execute();
	
	output = extractContentType(Packet, shell.getOutput());

	if (shell.getStatusCode() == STAT_SUCC)
	{
		if (!output.empty())
		{
			Packet.setStatusCode(200);
			Packet.setBody(output);
		}
		else
			Packet.setStatusCode(204);
	}
	else
	{
		if (shell.getStatusCode() == STAT_TMOUT)
			Packet.setStatusCode(504);
		else
			Packet.setStatusCode(500);
		if (!output.empty())
			Packet.setBody(output);
	}
}