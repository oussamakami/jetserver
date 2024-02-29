/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:57:29 by okamili           #+#    #+#             */
/*   Updated: 2024/02/25 11:34:11 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

std::vector<std::string> split(const std::string &str, const std::string &delimiter)
{
	size_t	start = 0;
	size_t	end = 0;
	std::vector<std::string>	result;

	do {
		end = str.find(delimiter, start);
		result.push_back(str.substr(start, end - start));
		start = end + delimiter.length();
	} while (end != std::string::npos);
	return (result);
}
