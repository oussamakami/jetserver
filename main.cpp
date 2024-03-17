/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 03:50:48 by okamili           #+#    #+#             */
/*   Updated: 2024/03/17 02:48:10 by okamili          ###   ########.fr       */
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
	handleConnections();

	terminate(0);
}
