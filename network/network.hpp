/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 07:54:24 by okamili           #+#    #+#             */
/*   Updated: 2024/06/09 14:54:47 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_HPP
# define NETWORK_HPP

# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include "./RequestParsing/RequestParsing.hpp"


void	setSockets(void);

void	prossessReq(void);

void	startServers(void);




void	generateResponse(int clientFD, ResponseData &data);
bool	handleGet(ResponseData &Packet);

#endif