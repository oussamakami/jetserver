/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classes.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 03:52:53 by okamili           #+#    #+#             */
/*   Updated: 2024/03/01 07:39:22 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSES_HPP
# define CLASSES_HPP

# include "SysData/SysData.hpp"
# include "Locations/Locations.hpp"
# include "Servers/Servers.hpp"


/**
 * @brief A namespace housing global configurations that determine the behavior of code components.
 * 
 * @note "system" configuration pertains to core system components, encompassing logging and CGI functionalities.
 * 
 */
namespace global
{
    extern SysData		*system;
	extern Servers		*servers;
}

#endif
