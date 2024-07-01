/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleDelete.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:53:32 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 19:43:21 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./generateResponse.hpp"

static int	deletePath(const std::string &fullPath)
{
	std::string	command;
	CommandLine	shell;

	if (fullPath.empty())
		return (STAT_FAIL);
	
	command = "/usr/bin/rm -rf ";
	command += fullPath;
	
	shell.setCommand(command);
	shell.execute();

	if (command[command.length() - 1] == '/')
	{
		shell.clearShell();
		command = "/usr/bin/mkdir ";
		command += fullPath;

		shell.setCommand(command);
		shell.execute();
	}
	return (shell.getStatusCode());
}

bool	handleDelete(ResponseData &Packet)
{
	std::string	RequestPath;
	std::string	FilePath;
	std::string	Temp;

	FilePath = Packet.getRequestPacket()->getFullPath();
	if (Packet.getRequestPacket()->getMethod() != "DELETE")
	{
		Packet.setStatusCode(403);
		return (true);
	}
	if (!doesExist(FilePath))
	{
		Packet.setStatusCode(404);
		return (true);
	}
	if (isFolder(FilePath))
	{
		if (FilePath[FilePath.length() - 1] != '/')
		{
			Packet.setStatusCode(409);
			return (true);
		}
		Temp = getIndexFile(FilePath, Packet.getRequestPacket()->getRoute());
		if (isCGI(Temp))
		{
			CGI_Delete(Packet, Temp);
			return (true);
		}
		if (deletePath(FilePath) == STAT_SUCC)
		{
			Packet.setStatusCode(204);
			return (true);
		}
	}
	else
	{
		if (isCGI(FilePath))
		{
			CGI_Delete(Packet, FilePath);
			return (true);
		}
		if(deletePath(FilePath) == STAT_SUCC)
		{
			Packet.setStatusCode(204);
			return (true);
		}
	}
	Packet.setStatusCode(500);
	return (true);
}