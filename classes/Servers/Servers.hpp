/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:20:18 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 13:19:35 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERS_HPP
# define SERVERS_HPP

# include "../Locations/Locations.hpp"
# include <vector>
# include <set>
# include <map>
# include <fstream>
# include <sstream>
# include <stdint.h>


/**
 * @brief Class for managing configuration and routing for a server.
 * 
 * @param setPort Sets the port number for the server to listen on.
 * @param setHost Sets the host for the server to listen on.
 * @param addDomain Adds a domain name to be linked with this server.
 * @param addError Adds a custom HTTP error page.
 * @param setRoutes Adds route rules to this server.
 * @param getPort Gets the port number the server is listening on.
 * @param getHost Gets the host the server is listening on.
 * @param hasDomain Checks if a domain name is linked to this server.
 * @param getDomains Gets all the domain names linked to this server.
 * @param getError Gets the HTML code for the error page.
 * @param getRoute Gets the route rules for the specified HTTP request path.
 * 
 */
class Servers
{
	private:
		uint16_t						_Port;
		std::string						_Host;
		std::set<std::string>			_Domain;
		std::map<size_t, std::string>	_ErrorPages;
		std::vector<Locations *>		_Routes;
	public:

		/**
		 * @brief Constructs a new Servers object.
		 */
		Servers(void);
		~Servers(void);

		/**
		 * @brief Sets the port number for the server to listen on.
		 * 
		 * @param PortNum The port number to set.
		 */
		void	setPort(const uint16_t PortNum);

		/**
		 * @brief Sets the host for the server to listen on.
		 * 
		 * @param Host The host to set.
		 */
		void	setHost(const std::string &Host);

		/**
		 * @brief Adds a domain name to be linked with this server.
		 * 
		 * @param DomainName The domain name to add.
		 */
		void	addDomain(const std::string &DomainName);

		/**
		 * @brief Adds a custom HTTP error page.
		 * 
		 * @param errorNum The error number.
		 * @param errorPath The path to the file for this error page.
		 */
		void	addError(const size_t errorNum, const std::string &errorPath);

		/**
		 * @brief Adds route rules to this server.
		 * 
		 * @param Route Pointer to the route object.
		 */
		void	setRoutes(Locations *Route);

		/**
		 * @brief Gets the port number the server is listening on.
		 * 
		 * @return uint16_t The port number.
		 */
		uint16_t					getPort(void) const;

		/**
		 * @brief Gets the host the server is listening on.
		 * 
		 * @return const std::string& The host.
		 */
		const std::string			&getHost(void) const;

		/**
		 * @brief Checks if a domain name is linked to this server.
		 * 
		 * @param DomainName The domain name to check.
		 * @return true if the domain name is linked, false otherwise.
		 */
		bool					hasDomain(const std::string &DomainName) const;

		/**
		 * @brief Gets all the domain names linked to this server.
		 * 
		 * @return const std::set<std::string>& Reference to the list containing the domain names.
		 */
		const std::set<std::string>	&getDomains(void) const;

		/**
		 * @brief Gets the HTML code for the error page.
		 * 
		 * @param errorNum The HTTP error number.
		 * @param msg The meaning of the HTTP error code (used for generating the default error page).
		 * @return const std::string HTML code for the error page.
		 */
		const std::string			getError(const size_t errorNum, const std::string &msg);

		/**
		 * @brief Gets the route rules for the specified HTTP request path.
		 * 
		 * @param ReqPath The requested path in the HTTP packet.
		 * @return Locations* Pointer to the route rules.
		 */
		Locations					*getRoute(const std::string &ReqPath);
};

#endif