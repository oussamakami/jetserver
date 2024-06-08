/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeCMD.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:22:16 by okamili           #+#    #+#             */
/*   Updated: 2024/06/06 18:10:56 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"
#include <cstring>
#include <sys/wait.h>

#define EXEC_FAIL 	1
#define	PIPE_FAIL 	2
#define	FORK_FAIL 	3
#define ALARM_FIRED 5

static char	**generateArguments(const std::string &command)
{
	std::vector<std::string>			table;
	char								**result;

	table = split(command, "|");
	result = new char*[table.size() + 1];
	result[table.size()] = NULL;

	for (int i = 0; i < table.size(); i++)
	{
		result[i] = new char[table.at(i).length() + 1];	
		std::strcpy(result[i], table.at(i).c_str());
	}
	return (result);
}

static void	clearMemo(char **args)
{
	for (int i = 0; args[i]; i++)
	{
		delete [] args[i];
	}
	delete [] args;
}

static std::string	readPipe(int fd)
{
	int			bytesReceived;
	char		buffer[1024];
	std::string	result = "";

	while (true)
	{
		bytesReceived = read(fd, buffer, 1023);
		if (bytesReceived > 0)
		{
			buffer[bytesReceived] = '\0';
			result += buffer;
		}
		else
			break;
	}

	return (result);
}

static int	runCMD(char **args, std::string &result)
{
	int	pipeFD[2];
	int status;
	pid_t	pid;

	if (pipe(pipeFD) == -1)
		return (PIPE_FAIL);

	pid = fork();
	if (pid == -1)
	{
		close(pipeFD[0]);
		close(pipeFD[1]);
		return (FORK_FAIL);
	}
	if (pid == 0)
	{
		close(pipeFD[0]);
		dup2(pipeFD[1], STDOUT_FILENO);
		close(pipeFD[1]);
		alarm(4);
		execve(args[0], args, NULL);
		exit(EXEC_FAIL);
	}
	else
	{
		close(pipeFD[1]);
		waitpid(pid, &status, 0);
		result = readPipe(pipeFD[0]);
		close(pipeFD[0]);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM)
			return (ALARM_FIRED);
		return (WEXITSTATUS(status));
	}
}

int	executeCMD(const std::string &command, std::string &result)
{
	int		status;
	char	**args;
	
	args = generateArguments(command);
	status = runCMD(args, result);
	clearMemo(args);

	return (status);
}
