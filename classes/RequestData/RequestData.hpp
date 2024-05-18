/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:00:10 by okamili           #+#    #+#             */
/*   Updated: 2024/05/18 15:33:13 by okamili          ###   ########.fr       */
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
# include <map>
# include "../Servers/Servers.hpp"

class RequestData
{
	private:
		size_t		_Size;
		std::string	_ClientIP;
		std::string _Method;
		std::string _Path;
		std::string	_Protocol;
		std::string	_Body;
		std::map<std::string, std::string>	_MetaData;
		Servers		*_Server;
	public:
		RequestData(void);
		RequestData(const std::string &clientIP);
		~RequestData(void);
		void	setSize(size_t newsize);
		void	setClientIP(const std::string &newIP);
		void	setMethod(const std::string &method);
		void	setPath(const std::string &path);
		void	setProtocol(const std::string &protocol);
		void	appendBody(const std::string &data);
		void	addMetaData(const std::string &key, const std::string &value);
		void	setServer(Servers *Data);

		const size_t		getSize(void) const;
		const std::string	getClientIP(void) const;
		const std::string	getMethod(void) const;
		const std::string	getPath(void) const;
		const std::string	getProtocol(void) const;
		const std::string	getBody(void) const;
		const std::string	getMetaData(const std::string &key) const;
		Servers				*getServer(void);
};

#endif
