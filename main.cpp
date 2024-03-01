/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 03:50:48 by okamili           #+#    #+#             */
/*   Updated: 2024/03/01 10:45:48 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing/parsing.hpp"

SysData	*global::system = new SysData();
Servers	*global::servers = NULL;

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
	{
	std::cout << "system:\n";
	std::cout << "LOG = " << global::system->getLogPath() << "\n";
	std::cout << "CGI = " << global::system->get_CGI() << "\n";
	std::cout << "CGI_EXT = " << global::system->get_CGI_Ext() << "\n";
	std::cout << "USE_CGI = " << (global::system->use_CGI() ? "True" : "False") << "\n";
	std::cout << "SIZE = " << global::system->getMaxSize() << "\n";
	std::cout << "DEVMODE = " << (global::system->DevMode() ? "True" : "False") << "\n";
	std::cout << "\nServer1:\n";
	std::cout << "PORT = " << global::servers->getPort() << "\n";
	std::cout << "HOST = " << global::servers->getHost() << "\n";
	std::set<std::string> holder = global::servers->getDomains();
	std::set<std::string>::iterator it = holder.begin();
	while (it != holder.end())
	{
		std::cout << "DOMAIN = " << *it << "\n";
		it++;
	}
	std::cout << "DOMAIN FACEBOOK.com EXIST = " << global::servers->hasDomain("FACEBOOK.com") << "\n";
	std::cout << "DOMAIN EXAMPLE3.com EXIST = " << global::servers->hasDomain("EXAMPLE3.com") << "\n";
	std::cout << "ERROR_502 = " << global::servers->getError(502) << "\n";
	holder.clear();
	std::cout << "\nServer2:\n";
	Servers *next = global::servers->getNext();
	holder = next->getDomains();
	it = holder.begin();
	std::cout << "PORT = " << next->getPort() << "\n";
	std::cout << "HOST = " << next->getHost() << "\n";
	while (it != holder.end())
	{
		std::cout << "DOMAIN = " << *it << "\n";
		it++;
	}
	}
	terminate(0);
}
