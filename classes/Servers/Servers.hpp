/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:20:18 by okamili           #+#    #+#             */
/*   Updated: 2024/03/02 09:49:15 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERS_HPP
# define SERVERS_HPP

# include "../Locations/Locations.hpp"
# include <set>
# include <map>
# include <fstream>
# include <sstream>
# include <stdint.h>

class Servers
{
	private:
		uint16_t						_Port;
		std::string						_Host;
		std::set<std::string>			_Domain;
		std::map<size_t, std::string>	_ErrorPages;
		Locations						*_Routes;
		Servers							*_Prev;
		Servers							*_Next;
	public:
		Servers(void);
		~Servers(void);
		void	setPort(const uint16_t PortNum);
		void	setHost(const std::string &Host);
		void	addDomain(const std::string &DomainName);
		void	addError(const size_t errorNum, const std::string &errorPath);
		void	setRoutes(Locations *Route);
		void	setNext(Servers *nextServer);
		uint16_t					getPort(void) const;
		const std::string			&getHost(void) const;
		const bool					hasDomain(const std::string &DomainName) const;
		const std::set<std::string>	&getDomains(void) const;
		const std::string			getError(const size_t errorNum);
		Servers						*getNext(void);
		Servers						*getPrev(void);
		//still need functions for getting the routes...
};

#endif
