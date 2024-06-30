/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 09:58:49 by okamili           #+#    #+#             */
/*   Updated: 2024/02/25 10:12:00 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

std::string trim(const std::string &str, const std::string &charList)
{
	size_t	head = str.find_first_not_of(charList);
	size_t	tail = str.find_last_not_of(charList);

	if (head != std::string::npos)
		return (str.substr(head, ++tail - head));
	return ("");
}