/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_Post.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 07:59:48 by okamili           #+#    #+#             */
/*   Updated: 2024/06/28 08:01:49 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generateResponse.hpp"

void	CGI_Post(ResponseData &Packet, const std::string &filePath)
{
	std::string	command;
	CommandLine	shell;

	command = global::system->get_CGI();
	command += " ";
	command += filePath;

	
}