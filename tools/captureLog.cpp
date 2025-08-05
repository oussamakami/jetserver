/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   captureLog.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:42:25 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 12:04:40 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

static std::string	getCurrentDate(void)
{
	time_t	rawTime = std::time(NULL);
	std::tm *timeInfo = std::localtime(&rawTime);
	
	std::stringstream	result;

	result << (timeInfo->tm_year + 1900) << "-";
	result << (timeInfo->tm_mon < 9 ? "0" : "") << timeInfo->tm_mon + 1 << "-";
	result << (timeInfo->tm_mday < 10 ? "0" : "") << timeInfo->tm_mday << " ";
	result << (timeInfo->tm_hour < 10 ? "0" : "") << timeInfo->tm_hour << ":";
	result << (timeInfo->tm_min < 10 ? "0" : "") << timeInfo->tm_min << ":";
	result << (timeInfo->tm_sec < 10 ? "0" : "") << timeInfo->tm_sec;
	return (result.str());
}

void	captureLog(ResponseData &Packet)
{
	std::stringstream	Log;
	
	Log << getCurrentDate() << " [JetServer] Host: ";
	Log << Packet.getRequestPacket()->getMetaData("Host");
	Log << ", IP: " << Packet.getRequestPacket()->getClientIP();
	Log << " -> (" << Packet.getRequestPacket()->getMethod();
	Log << ") " << Packet.getRequestPacket()->getPath() << " ";
	Log << "[Status " << Packet.getStatusCode() << "]";

	notify(global::system->getLogStream(), "%s", Log.str().c_str());
}