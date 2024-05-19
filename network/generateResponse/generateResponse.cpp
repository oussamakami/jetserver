/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:02:48 by okamili           #+#    #+#             */
/*   Updated: 2024/05/19 11:58:14 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../network.hpp"

void	generateResponse(int clientFD, RequestData &data)
{
	std::string response = "HTTP/1.1 200 OK\r\n"
                       "Content-Type: text/html\r\n"
                       "Content-Length: 225\r\n\r\n";

	if (data.getServer())
		response += global::servers->at(0)->getError(500);
	else
		response += global::servers->at(0)->getError(404);

	notify(std::cout, "the host: %s", data.getMetaData("Host").c_str());
	if (data.getServer())
		notify(std::cout, "server found: %s:%d", data.getServer()->getHost().c_str(), data.getServer()->getPort());
	write(clientFD, response.c_str(), response.length());
}
