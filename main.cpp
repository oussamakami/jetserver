/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 03:50:48 by okamili           #+#    #+#             */
/*   Updated: 2024/02/29 14:18:44 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing/parsing.hpp"

SysData	*global::system = new SysData();

static void handleArgs(int argc, char **argv)
{
	bool	status = false;

	switch (argc)
	{
		case 1:
			status = loadConfig("./webserver.conf");
			break;
		case 2:
			status = loadConfig(argv[1]);
			break;
		default:
			notify(std::cerr, "%EInvalid number of arguments.");
	}
	if (!status)
		terminate(2);
}

int main(int argc, char **argv)
{
	handleArgs(argc, argv);

	std::cout << "system:\n";
	std::cout << "LOG = " << global::system->getLogPath() << "\n";
	std::cout << "CGI = " << global::system->get_CGI() << "\n";
	std::cout << "CGI_EXT = " << global::system->get_CGI_Ext() << "\n";
	std::cout << "USE_CGI = " << (global::system->use_CGI() ? "True" : "False") << "\n";
	std::cout << "SIZE = " << global::system->getMaxSize() << "\n";
	std::cout << "DEVMODE = " << (global::system->DevMode() ? "True" : "False") << "\n";

	terminate(0);
}
