/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_Get.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 04:56:55 by okamili           #+#    #+#             */
/*   Updated: 2024/06/28 08:00:56 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generateResponse.hpp"

void	CGI_Get(ResponseData &Packet, const std::string &filePath)
{
	std::string	command;
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

	shell.execute();
	
	if (shell.getStatusCode() == STAT_SUCC)
	{
		Packet.setBody(shell.getOutput());
		Packet.setStatusCode(200);
	}
	else
	{
		Packet.setStatusCode(500);
		if (!shell.getOutput().empty())
			Packet.setBody(shell.getOutput());
	}
}