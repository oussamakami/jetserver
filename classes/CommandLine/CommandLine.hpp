/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandLine.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:38:46 by okamili           #+#    #+#             */
/*   Updated: 2024/06/28 07:27:53 by okamili          ###   ########.fr       */
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
		CommandLine(void);
		CommandLine(const std::string &cmd);
		~CommandLine(void);

		void	setCommand(const std::string &cmd);
		void	setInput(const std::string &inputData);
		void	addEnv(const std::string &key, const std::string &value);
		void	clearEnv(void);
		void	execute(void);
		void	clearShell(void);

		const std::string	&getCommand(void) const;
		const std::string	&getInput(void) const;
		const std::string	&getOutput(void) const;
		int					getStatusCode(void) const;
};

#endif
