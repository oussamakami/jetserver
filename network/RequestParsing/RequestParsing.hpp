/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParsing.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:30:06 by okamili           #+#    #+#             */
/*   Updated: 2024/05/18 17:40:49 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTPARSING_HPP
# define REQUESTPARSING_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include "../../classes/classes.hpp"
# include "../../tools/tools.hpp"

bool	extractData(const std::string &packet, RequestData &Data);
void	getServer(RequestData &Data);

bool	requestParsing(int clientFD, std::map<int, RequestData> &packets);

#endif