/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandLine.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:05:22 by okamili           #+#    #+#             */
/*   Updated: 2024/06/28 07:50:57 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandLine.hpp"

void	CommandLine::releaseMemory(char **data)
{
	if (!data)
		return ;
	for (int i = 0; data[i]; i++)
		delete [] data[i];
	delete [] data;
}

CommandLine::CommandLine(void)
{
	this->status = STAT_SUCC;
	this->cmd = "";
	this->input = "";
	this->output = "";
	this->cmdArgs = NULL;
	this->cmdEnvs = NULL;
}

CommandLine::CommandLine(const std::string &cmd)
{
	this->status = STAT_SUCC;
	this->cmd = cmd;
	this->input = "";
	this->output = "";
	this->cmdArgs = NULL;
	this->cmdEnvs = NULL;
}

CommandLine::~CommandLine(void)
{
	releaseMemory(cmdArgs);
	releaseMemory(cmdEnvs);
}

void	CommandLine::setCommand(const std::string &cmd)
{
	this->cmd = cmd;
}

void	CommandLine::setInput(const std::string &inputData)
{
	this->input = inputData;
}

void	CommandLine::addEnv(const std::string &key, const std::string &value)
{
	std::string temp;

	temp = key;
	temp += "=";
	temp += value;

	this->envData.push_back(temp);
}

void	CommandLine::clearEnv(void)
{
	this->envData.clear();
}

void	CommandLine::clearShell(void)
{
	releaseMemory(cmdArgs);
	releaseMemory(cmdEnvs);
	this->envData.clear();
	this->status = STAT_SUCC;
	this->cmd = "";
	this->input = "";
	this->output = "";
	this->cmdArgs = NULL;
	this->cmdEnvs = NULL;
}

const std::string	&CommandLine::getCommand(void) const
{
	return (this->cmd);
}

const std::string	&CommandLine::getInput(void) const
{
	return (this->input);
}

const std::string	&CommandLine::getOutput(void) const
{
	return (this->output);
}

int	CommandLine::getStatusCode(void) const
{
	return (this->status);
}

void	CommandLine::generateArgs(void)
{
	std::vector<std::string>			table;
	char								**result;

	table = split(this->cmd, " ");
	result = new char*[table.size() + 1];
	result[table.size()] = NULL;

	for (int i = 0; i < table.size(); i++)
	{
		result[i] = new char[table.at(i).length() + 1];	
		std::strcpy(result[i], table.at(i).c_str());
	}
	if (this->cmdArgs)
		releaseMemory(this->cmdArgs);
	this->cmdArgs = result;
}

void	CommandLine::generateEnvs(void)
{
	char		**result;
	
	result = new char*[envData.size() + 1];
	result[envData.size()] = NULL;
	
	for (int i = 0; i < envData.size(); i++)
	{
		result[i] = new char[envData.at(i).length() + 1];	
		std::strcpy(result[i], envData.at(i).c_str());
	}
	if (this->cmdEnvs)
		releaseMemory(this->cmdEnvs);
	this->cmdEnvs = result;
}

static void runCommandLine(char **args, char **envs, int inPipe[2], int outPipe[2])
{
	close(inPipe[1]);
	close(outPipe[0]);
	dup2(inPipe[0], STDIN_FILENO);
	dup2(outPipe[1], STDOUT_FILENO);
	dup2(outPipe[1], STDERR_FILENO);
	close(inPipe[0]);
	close(outPipe[1]);
	alarm(8);
	execve(args[0], args, envs);
	exit(STAT_FAIL);	
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

void	CommandLine::execute(void)
{
	int		inputPipe[2];
	int		outputPipe[2];
	int		status;
	pid_t	pid;

	generateArgs();
	generateEnvs();

	if (!this->cmdArgs || !this->cmdArgs[0])
	{
		this->status = STAT_FAIL;
		return ;
	}

	if (pipe(inputPipe) == -1 || pipe(outputPipe) == -1)
	{
		this->status = STAT_ERR;
		return ;
	}

	if (!this->input.empty())
	{
		if (write(inputPipe[1], this->input.c_str(), this->input.length()) == -1)
		{
			close(inputPipe[0]);
			close(inputPipe[1]);
			close(outputPipe[0]);
			close(outputPipe[1]);
			this->status = STAT_ERR;
			return ;
		}
		close(inputPipe[1]);
	}
	pid = fork();
	if (pid == -1)
	{
		close(inputPipe[0]);
		close(inputPipe[1]);
		close(outputPipe[0]);
		close(outputPipe[1]);
		this->status = STAT_ERR;
		return ;
	}
	if (pid == 0)
		runCommandLine(this->cmdArgs, this->cmdEnvs, inputPipe, outputPipe);
	else
	{
		waitpid(pid, &status, 0);
		close(inputPipe[0]);
		close(outputPipe[1]);
		this->output = readPipe(outputPipe[0]);
		close(outputPipe[0]);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM)
			this->status = STAT_TMOUT;
		else
			this->status = WEXITSTATUS(status);
	}
}
