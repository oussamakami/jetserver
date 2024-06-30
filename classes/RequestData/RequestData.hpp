/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:00:10 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 13:18:00 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTDATA_HPP
# define REQUESTDATA_HPP

# include <iostream>
# include <map>
# include "../Servers/Servers.hpp"


/**
 * @brief Class for managing data from an HTTP request packet.
 * 
 * @param setSize Set the size of the received HTTP request packet.
 * @param setClientIP Set the client IP address that sent the HTTP request.
 * @param setMethod Set the HTTP method used by the received request.
 * @param setPath Set the path requested by the received HTTP request.
 * @param setProtocol Set the HTTP protocol used by the received HTTP request.
 * @param appendBody Append the body data of the received HTTP request to any previously parsed body.
 * @param addMetaData Add and store metadata received in the HTTP request header.
 * @param setServer Set the server responsible for receiving the HTTP request.
 * @param getSize Get the size of the HTTP request.
 * @param getClientIP Get the client IP address that sent the HTTP request.
 * @param getMethod Get the HTTP method used by the request.
 * @param getPath Get the path requested by the HTTP packet.
 * @param getFullPath Get the full system path corresponding to the requested path in the HTTP packet.
 * @param getProtocol Get the protocol used by the received HTTP request.
 * @param getBody Get the body data of the received HTTP request.
 * @param getMetaData Get the value of a metadata item from the received HTTP request.
 * @param getServer Get the server responsible for receiving the HTTP request.
 * @param getRoute Get the system route corresponding to the path requested by the HTTP packet.
 * 
 */
class RequestData
{
	private:
		size_t								_Size;
		std::string							_ClientIP;
		std::string 						_Method;
		std::string 						_Path;
		std::string 						_FullPath;
		std::string							_Protocol;
		std::string							_Body;
		std::map<std::string, std::string>	_MetaData;
		Servers		*_Server;
		Locations	*_Route;
	public:

		/**
		 * @brief  Constructs an empty RequestData class.
		 */
		RequestData(void);

		/**
		 * @brief Constructs a RequestData class with the client IP address.
		 * 
		 * @param clientIP The client IP address.
		 */
		RequestData(const std::string &clientIP);
		~RequestData(void);

		/**
		 * @brief Set the size of the received HTTP request packet.
		 * 
		 * @param newsize The size of the packet.
		 */
		void	setSize(size_t newsize);

		/**
		 * @brief Set the client IP address that sent the HTTP request.
		 * 
		 * @param newIP The client IP address.
		 */
		void	setClientIP(const std::string &newIP);

		/**
		 * @brief Set the HTTP method used by the received request.
		 * 
		 * @param method The HTTP method name.
		 */
		void	setMethod(const std::string &method);

		/**
		 * @brief Set the path requested by the received HTTP request.
		 * 
		 * @param path The path requested.
		 */
		void	setPath(const std::string &path);

		/**
		 * @brief Set the HTTP protocol used by the received HTTP request.
		 * 
		 * @param protocol The protocol name and version.
		 */
		void	setProtocol(const std::string &protocol);

		/**
		 * @brief Append the body data of the received HTTP request to any previously parsed body.
		 * 
		 * @param data The body data of the request to append.
		 */
		void	appendBody(const std::string &data);

		/**
		 * @brief Add and store metadata received in the HTTP request header.
		 * 
		 * @param key The metadata name.
		 * @param value The metadata value.
		 */
		void	addMetaData(const std::string &key, const std::string &value);

		/**
		 * @brief Set the server responsible for receiving the HTTP request.
		 * 
		 * @param Data Pointer to the server object handling the HTTP request.
		 */
		void	setServer(Servers *Data);

		/**
		 * @brief Get the size of the HTTP request.
		 * 
		 * @return const size_t The size of the received request.
		 */
		size_t		getSize(void) const;

		/**
		 * @brief Get the client IP address that sent the HTTP request.
		 * 
		 * @return const std::string The client IP address.
		 */
		const std::string	getClientIP(void) const;

		/**
		 * @brief Get the HTTP method used by the request.
		 * 
		 * @return const std::string The HTTP method name.
		 */
		const std::string	getMethod(void) const;

		/**
		 * @brief Get the path requested by the HTTP packet.
		 * 
		 * @return const std::string The requested path.
		 */
		const std::string	getPath(void) const;

		/**
		 * @brief Get the full system path corresponding to the requested path in the HTTP packet.
		 * 
		 * @return const std::string The full system path.
		 */
		const std::string	getFullPath(void) const;

		/**
		 * @brief Get the protocol used by the received HTTP request.
		 * 
		 * @return const std::string The protocol name and version.
		 */
		const std::string	getProtocol(void) const;

		/**
		 * @brief Get the body data of the received HTTP request.
		 * 
		 * @return const std::string The body data of the HTTP request.
		 */
		const std::string	getBody(void) const;

		/**
		 * @brief Get the value of a metadata item from the received HTTP request.
		 * 
		 * @param key The name of the metadata.
		 * @return const std::string The value of the metadata.
		 */
		const std::string	getMetaData(const std::string &key) const;

		/**
		 * @brief Get the server responsible for receiving the HTTP request.
		 * 
		 * @return Servers* Pointer to the server object.
		 */
		Servers				*getServer(void);

		/**
		 * @brief Get the system route corresponding to the path requested by the HTTP packet.
		 * 
		 * @return Locations* Pointer to the route object.
		 */
		Locations			*getRoute(void);
};

#endif