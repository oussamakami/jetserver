/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathCombs.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:54:18 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 12:12:24 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

std::vector<std::string>	pathCombs(const std::string &path)
{
	std::vector<std::string>	result;
	std::vector<std::string>	words;
	std::string joined = "/";

	words = split(path, "/");
	result.push_back(joined);
	for (size_t i = 0; i < words.size(); i++)
	{
		if (words.at(i).empty())
			continue;
		joined += words.at(i) + "/";
		result.push_back(joined);
	}
	std::reverse(result.begin(), result.end());
	return (result);
}