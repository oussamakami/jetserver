/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:57:29 by okamili           #+#    #+#             */
/*   Updated: 2024/05/18 16:49:35 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

std::vector<std::string> split(const std::string &str, const std::string &delimiter)
{
	size_t						start = 0;
	size_t						end = 0;
	std::string					holder;
	std::vector<std::string>	result;

	do {
		end = str.find(delimiter, start);

		holder = str.substr(start, end - start);
		if (holder[holder.length() - 1] == '\r')
			holder[holder.length() - 1] = '\0';

		result.push_back(holder);
		start = end + delimiter.length();
	} while (end != std::string::npos);

	return (result);
}
