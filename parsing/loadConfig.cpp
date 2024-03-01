/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadConfig.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 09:16:01 by okamili           #+#    #+#             */
/*   Updated: 2024/03/01 06:53:36 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

bool	loadConfig(std::string confPath)
{
	std::ifstream	source;
	std::string		holder;

	if (!isConfigFile(confPath) || !fileExist(confPath))
		return (false);

	source.open(confPath.c_str());
	for (size_t fileLine = 1; getline(source, holder); fileLine++)
	{
		holder = trim(holder, "\t\r\n ");
		if (holder.empty() || holder[0] == '#')
			continue;
		if (holder == "START_SYSTEM" && !parseSystem(source, fileLine))
			return (false);
		else if (holder == "START_SERVER" && !parseServers(source, fileLine))
			return (false);
		else if (holder != "START_SYSTEM" && holder != "START_SERVER")
		{
			notify(std::cerr, "%EUnknown option \"%s\" on line %d.", holder.c_str(), fileLine);
			return (false);
		}
	}
	return (true);
}
