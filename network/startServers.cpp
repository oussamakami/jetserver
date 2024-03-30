/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startServers.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:46:04 by okamili           #+#    #+#             */
/*   Updated: 2024/03/30 09:01:58 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.hpp"

void	startServers(void)
{
	setSockets();
	while(true)
		prossessReq();
}
