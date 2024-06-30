/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startServers.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:46:04 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 14:02:55 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.hpp"

void	startServers(void)
{
	setSockets();
	while(true)
		prossessReq();
}