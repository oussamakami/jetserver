/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isCGI.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 07:14:44 by okamili           #+#    #+#             */
/*   Updated: 2024/06/27 07:26:35 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

bool	isCGI(const std::string &fullPath)
{
	std::vector<std::string> temp;

	if (isFolder(fullPath) || !global::system->use_CGI())
		return (false);
	temp = split(fullPath, ".");
	if (temp.size() < 2)
		return (false);
	return (temp.back() == global::system->get_CGI_Ext());
}