/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePost.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 00:57:35 by okamili           #+#    #+#             */
/*   Updated: 2024/06/11 01:40:20 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../network.hpp"

/*

-----------------------------201969339419841559181262827122
Content-Disposition: form-data; name="file"; filename="hello.txt"
Content-Type: text/plain

In the vast tapestry of existence, where time weaves its intricate patterns through the fabric of reality, each moment is a thread, each event a stitch, binding the past to the present and the future. From the cosmic dance of stars to the microscopic world of atoms, from the birth of galaxies to the flutter of a butterfly's wings, everything is connected, everything is intertwined in the intricate web of existence. We are but fleeting sparks in the grand symphony of the universe, our lives mere whispers in the eternal silence of time. Yet, in our brief moment in the sun, we have the power to shape the world, to leave our mark on the tapestry of existence. We are the architects of our own destiny, the masters of our fate. But with this power comes responsibility, for every action we take, every choice we make, ripples through the fabric of reality, shaping the world around us in ways we cannot always foresee. It is up to us to choose wisely, to act with compassion and kindness, to leave the world a better place than we found it. For in the end, it is not the wealth we amass or the power we wield that defines us, but the love we share, the kindness we show, the legacy of compassion we leave behind. So let us live each day with purpose and passion, let us strive to be the best version of ourselves, let us be the change we wish to see in the world. For in the tapestry of existence, every thread counts, every stitch matters, and together, we can create a masterpiece of love, peace, and harmony that will endure for eternity.
-----------------------------201969339419841559181262827122--

*/

static	std::string	getSaveFileName(const std::string &body)
{
	
}

bool	handlePost(ResponseData &Packet)
{
	std::string	requestPath;
	std::string	fullPath;
	Locations	*route;

	requestPath = Packet.getRequestPacket()->getPath();
	fullPath = Packet.getRequestPacket()->getFullPath();
	route = Packet.getRequestPacket()->getRoute();
	
	// if (!route->useMethod("POST"))
	// {
	// 	Packet.setStatusCode(405);
	// 	return (true);
	// }
	// if (!doesExist(fullPath))
	// {
	// 	Packet.setStatusCode(404);
	// 	return (true);
	// }
	// if (isFolder(fullPath))
	// {
	// 	if (getIndexFile(fullPath, requestPath, Packet.getRequestPacket()->getRoute()).empty())
	// 		Packet.setStatusCode(403);
	// 	else
	// 	{
	// 		//if index is cgi run cgi
	// 		//else send 403 
	// 	}
	// }
	// //if index is cgi run cgi
	// //else send 403 
	return (true);
}