/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringtoInt.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:42:56 by okamili           #+#    #+#             */
/*   Updated: 2024/05/17 09:51:45 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

std::string	intToString(int num)
{
	std::stringstream ss;

	ss << num;

	return (ss.str());
}

int	StringToInt(const std::string &num)
{
	std::stringstream ss;
	int	result = 0;

	ss << num;
	ss >> result;

	return (result);
}
