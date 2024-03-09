/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 03:50:48 by okamili           #+#    #+#             */
/*   Updated: 2024/03/09 17:37:35 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing/parsing.hpp"
# include "network/network.hpp"

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
	setSockets();
	// {
	// std::cout << "system:\n";
	// std::cout << "LOG = " << global::system->getLogPath() << "\n";
	// std::cout << "CGI = " << global::system->get_CGI() << "\n";
	// std::cout << "CGI_EXT = " << global::system->get_CGI_Ext() << "\n";
	// std::cout << "USE_CGI = " << (global::system->use_CGI() ? "True" : "False") << "\n";
	// std::cout << "SIZE = " << global::system->getMaxSize() << "\n";
	// std::cout << "DEVMODE = " << (global::system->DevMode() ? "True" : "False") << "\n";
	// std::cout << "\nServer1:\n";
	// std::cout << "PORT = " << global::servers->getPort() << "\n";
	// std::cout << "HOST = " << global::servers->getHost() << "\n";
	// std::set<std::string> holder = global::servers->getDomains();
	// holder.clear();
	// holder = global::servers->getDomains();
	// std::set<std::string>::iterator it = holder.begin();
	// while (it != holder.end())
	// {
	// 	std::cout << "DOMAIN = " << *it << "\n";
	// 	it++;
	// }
	// std::cout << "DOMAIN FACEBOOK.com EXIST = " << global::servers->hasDomain("FACEBOOK.com") << "\n";
	// std::cout << "DOMAIN EXAMPLE3.com EXIST = " << global::servers->hasDomain("EXAMPLE3.com") << "\n";
	// std::cout << "ERROR_502 = " << global::servers->getError(502) << "\n\n";
	// std::cout << "\nServer2:\n";
	// Servers *next = global::servers->getNext();
	// holder = next->getDomains();
	// it = holder.begin();
	// std::cout << "PORT = " << next->getPort() << "\n";
	// std::cout << "HOST = " << next->getHost() << "\n";
	// while (it != holder.end())
	// {
	// 	std::cout << "DOMAIN = " << *it << "\n";
	// 	it++;
	// }
	// }

	
	// int newsocket;
	// struct sockaddr_in address;
	// int addresslen = sizeof(address);
	// std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
	// hello += global::servers->getError(500);

	// char ip_address[INET_ADDRSTRLEN];
    // struct sockaddr_in* client_addr;

	// while(1)
    // {
    //     notify(std::cout, "+++++++ Waiting for new connection ++++++++\n");
	// 	newsocket = accept(global::system->getSockets().at(0), (struct sockaddr *)&address, (socklen_t*)&addresslen);
	// 	client_addr = (struct sockaddr_in*)&address;
	// 	inet_ntop(AF_INET, &(client_addr->sin_addr), ip_address, INET_ADDRSTRLEN);
    //     char buffer[30000] = {0};
    //     read(newsocket , buffer, 30000);
    //     notify(std::cout, "%s\n",buffer );
    //     write(newsocket , hello.c_str() , hello.length());
	// 	notify(std::cout, "%W%s", ip_address);
    //     notify(std::cout, "------------------Hello message sent-------------------\n");
	// 	close(newsocket);
    // }

	terminate(0);
}
