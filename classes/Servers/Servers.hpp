/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:20:18 by okamili           #+#    #+#             */
/*   Updated: 2024/03/01 10:40:43 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERS_HPP
# define SERVERS_HPP

# include "../Locations/Locations.hpp"
# include <set>
# include <map>
# include <fstream>
# include <sstream>

class Servers
{
	private:
		size_t							_Port;
		std::string						_Host;
		std::set<std::string>			_Domain;
		std::map<size_t, std::string>	_ErrorPages;
		Locations						*_Routes;
		Servers							*_Prev;
		Servers							*_Next;
	public:
		Servers(void);
		~Servers(void);
		void	setPort(const size_t PortNum);
		void	setHost(const std::string &Host);
		void	addDomain(const std::string &DomainName);
		void	addError(const size_t errorNum, const std::string &errorPath);
		void	setRoutes(Locations *Route);
		void	setNext(Servers *nextServer);
		size_t						getPort(void) const;
		const std::string			&getHost(void) const;
		const bool					hasDomain(const std::string &DomainName) const;
		const std::set<std::string>	&getDomains(void) const;
		const std::string			getError(const size_t errorNum);
		Servers						*getNext(void);
		Servers						*getPrev(void);
};

#endif
