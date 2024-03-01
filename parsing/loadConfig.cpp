/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadConfig.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 09:16:01 by okamili           #+#    #+#             */
/*   Updated: 2024/03/01 18:56:56 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

bool	loadConfig(std::string confPath)
{
	std::ifstream	source;
	std::string		trimedStr;

	if (!isConfigFile(confPath) || !fileExist(confPath))
		return (false);

	source.open(confPath.c_str());
	for (size_t fileLine = 1; getline(source, trimedStr); fileLine++)
	{
		trimedStr = trim(trimedStr, "\t\r\n\"'; |");
		if (trimedStr.empty() || trimedStr[0] == '#')
			continue;
		if (trimedStr == "START_SYSTEM" && !parseSystem(source, ++fileLine))
			return (false);
		else if (trimedStr == "START_SERVER" && !parseServers(source, ++fileLine))
			return (false);
		else if (trimedStr != "START_SYSTEM" && trimedStr != "START_SERVER")
		{
			notify(std::cerr, "%EUnknown option \"%s\" on line %d.", trimedStr.c_str(), fileLine);
			return (false);
		}
	}
	notify(std::cout, "%IConfiguration successfully loaded.");
	return (true);
}
