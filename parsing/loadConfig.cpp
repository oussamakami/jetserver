/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadConfig.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 09:16:01 by okamili           #+#    #+#             */
/*   Updated: 2024/02/29 07:44:58 by okamili          ###   ########.fr       */
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
		{
			source.close();
			return (false);
		}
	}
	source.close();
	return (true);
}
