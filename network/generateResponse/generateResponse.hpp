/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateResponse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:20:32 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 19:08:45 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATERESPONSE_HPP
# define GENERATERESPONSE_HPP

# include "../RequestParsing/RequestParsing.hpp"


void	generateResponse(int clientFD, ResponseData &data);
bool	handleGet(ResponseData &Packet);
bool	handlePost(ResponseData &Packet);
bool	handleDelete(ResponseData &Packet);

void	CGI_Get(ResponseData &Packet, const std::string &filePath);
void	CGI_Post(ResponseData &Packet, const std::string &filePath);
void	CGI_Delete(ResponseData &Packet, const std::string &filePath);


#endif