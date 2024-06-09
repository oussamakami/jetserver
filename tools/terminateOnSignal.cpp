/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminateOnSignal.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:22:25 by okamili           #+#    #+#             */
/*   Updated: 2024/06/09 17:00:38 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

static void	signalHandler(int signal)
{
	if (signal == SIGINT)
		terminate(0);
	if (signal == SIGTERM)
		terminate(1);
}

void	terminateOnSignal(void)
{
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGPIPE, signalHandler);
}