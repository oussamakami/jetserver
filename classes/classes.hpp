/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classes.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 03:52:53 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 11:19:58 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSES_HPP
# define CLASSES_HPP

# include "SysData/SysData.hpp"
# include "Locations/Locations.hpp"
# include "RequestData/RequestData.hpp"
# include "ResponseData/ResponseData.hpp"
# include "CommandLine/CommandLine.hpp"


/**
 * @brief A namespace housing global configurations that determine the behavior of code components.
 * 
 * @note "system" configuration pertains to core system components, encompassing logging, CGI and other functionalities.
 * @note "servers" stores servers configurations such as the host, port, error pages, domains, and routes.
 * 
 */
namespace global
{
    extern SysData					*system;
	extern std::vector<Servers *>	*servers;
}

#endif