/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 07:54:24 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 14:08:18 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_HPP
# define NETWORK_HPP

# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include "./RequestParsing/RequestParsing.hpp"
# include "./generateResponse/generateResponse.hpp"

/**
 * @brief Creates and starts listening on sockets.
 */
void	setSockets(void);

/**
 * @brief Manages the accepted connections and processes each request.
 */
void	prossessReq(void);

/**
 * @brief Starts listening on sockets and processes each incoming request.
 */
void	startServers(void);

#endif