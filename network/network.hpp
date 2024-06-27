/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 07:54:24 by okamili           #+#    #+#             */
/*   Updated: 2024/06/23 07:11:35 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_HPP
# define NETWORK_HPP

# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include "./RequestParsing/RequestParsing.hpp"
# include "./generateResponse/generateResponse.hpp"


void	setSockets(void);

void	prossessReq(void);

void	startServers(void);

#endif