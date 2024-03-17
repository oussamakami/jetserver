/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 07:54:24 by okamili           #+#    #+#             */
/*   Updated: 2024/03/17 02:45:37 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_HPP
# define NETWORK_HPP

# include "../classes/classes.hpp"
# include "../tools/tools.hpp"
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>

void	setSockets(void);
void	handleConnections(void);

#endif