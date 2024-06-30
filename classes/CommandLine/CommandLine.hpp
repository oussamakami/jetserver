/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandLine.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:38:46 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 13:15:41 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDLINE_HPP
# define COMMANDLINE_HPP

# define STAT_SUCC	0
# define STAT_FAIL	1
# define STAT_ERR	2
# define STAT_TMOUT	3

# include <cstring>
# include <sys/wait.h>
# include "../../tools/tools.hpp"


/**
 * @brief Class for executing shell commands and managing their environment.
 * 
 * @param setCommand Sets the shell Command.
 * @param setInput Sets the input for the shell command.
 * @param addEnv Adds environment variables to the shell.
 * @param clearEnv Clears all environment variables from the shell.
 * @param execute Executes the shell command.
 * @param clearShell Clears and resets the shell.
 * @param getCommand Retrieves the shell command.
 * @param getInput Retrieves the input data for the shell command.
 * @param getOutput Retrieves the output data from the shell execution.
 * @param getStatusCode Retrieves the shell termination status.
 * 
 */
class CommandLine
{
	private:
		int									status;
		std::string							cmd;
		std::string							input;
		std::string							output;
		std::vector<std::string>			envData;
		char								**cmdArgs;
		char								**cmdEnvs;
		void								generateArgs(void);
		void								generateEnvs(void);
		void								releaseMemory(char **data);
	public:

		/**
		 * @brief Initialize an empty CommandLine object.
		 */
		CommandLine(void);

		/**
		 * @brief Constructs a CommandLine object with the specified command.
		 * 
		 * @param cmd The shell command to be executed.
		 */
		CommandLine(const std::string &cmd);
		~CommandLine(void);

		/**
		 * @brief Sets the shell Command.
		 * 
		 * @param cmd The shell command to be executed.
		 */
		void	setCommand(const std::string &cmd);

		/**
		 * @brief Sets the input for the shell command.
		 * 
		 * @param inputData The input data to be provided to the command.
		 */
		void	setInput(const std::string &inputData);

		/**
		 * @brief Adds environment variables to the shell.
		 * 
		 * @param key The name of the environment variable.
		 * @param value The value of the environment variable.
		 */
		void	addEnv(const std::string &key, const std::string &value);

		/**
		 * @brief Clears all environment variables from the shell.
		 */
		void	clearEnv(void);

		/**
		 * @brief Executes the shell command.
		 */
		void	execute(void);

		/**
		 * @brief Clears and resets the shell.
		 */
		void	clearShell(void);

		/**
		 * @brief Retrieves the shell command.
		 * 
		 * @return const std::string& Reference to the shell command string.
		 */
		const std::string	&getCommand(void) const;

		/**
		 * @brief Retrieves the input data for the shell command.
		 * 
		 * @return const std::string& Reference to the input data.
		 */
		const std::string	&getInput(void) const;

		/**
		 * @brief Retrieves the output data from the shell execution.
		 * 
		 * @return const std::string& Reference to the output data.
		 */
		const std::string	&getOutput(void) const;

		/**
		 * @brief Retrieves the shell termination status.
		 * 
		 * @return int The status code of the shell.
		 */
		int					getStatusCode(void) const;
};

#endif