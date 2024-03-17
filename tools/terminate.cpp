/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 09:22:06 by okamili           #+#    #+#             */
/*   Updated: 2024/03/17 05:57:40 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

void	terminate(unsigned char errorCode)
{
	std::vector<Servers *>::iterator it;

	it = global::servers->begin();
	while (it != global::servers->end())
	{
		delete (*it);
		it++;
	}
	delete global::servers;
	delete global::system;
	exit(errorCode);
}
