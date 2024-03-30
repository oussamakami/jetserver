/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:00:10 by okamili           #+#    #+#             */
/*   Updated: 2024/03/29 10:06:37 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// GET / HTTP/1.1
// Host: 127.0.0.1:8080
// User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:124.0) Gecko/20100101 Firefox/124.0
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate, br
// Connection: keep-alive
// Upgrade-Insecure-Requests: 1
// Sec-Fetch-Dest: document
// Sec-Fetch-Mode: navigate
// Sec-Fetch-Site: none
// Sec-Fetch-User: ?1

#ifndef REQUESTDATA_HPP
# define REQUESTDATA_HPP

# include <iostream>
# include "../Servers/Servers.hpp"

class RequestData
{
	private:
		size_t		_size;
		std::string	_clientIP;
		std::string _method;
		std::string _path;
		std::string _protocol;
		std::string _host;
		bool		_keep_alive;
		Servers		*_server;
	public:
		RequestData(void);
		RequestData(const std::string &clientIP);
		~RequestData(void);
		void	setSize(size_t newsize);
		void	setIP(const std::string &newIP);
		void	setMethod(const std::string &method);
		void	setProtocol(const std::string &proto);
		void	setHost(const std::string &host);
		void	stayAlive(bool status);

		const size_t		getSize(void) const;
		const std::string	getIP(void) const;
		const std::string	getMethod(void) const;
		const std::string	getPath(void) const;
		const std::string	getProtocol(void) const;
		const std::string	getHost(void) const;
		const bool			isStayAlive(void) const;
		Servers				&getServer(void);
		
};

#endif