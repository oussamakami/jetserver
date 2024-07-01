/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SysData.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 03:26:09 by okamili           #+#    #+#             */
/*   Updated: 2024/07/01 07:56:40 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSDATA_HPP
# define SYSDATA_HPP

# include <iostream>
# include <fstream>
# include <vector>
# include <unistd.h>
# include <poll.h>
# include <set>
# include <map>

class RequestData;
class ResponseData;

/**
 * @brief This class encapsulates system configuration settings
 * related to the log file, CGI, etc...
 * 
 * @param setMaxBodySize Define the maximum size, in bytes, for packets that the client can transmit.
 * @param setLogPath Specify the log file to be utilized by the system.
 * @param set_CGI Specify the CGI program.
 * @param set_CGI_Ext Specify the CGI extension to handle.
 * @param addSocket Append a socket file descriptor (fd) to the sockets list.
 * @param addClient Append a client file descriptor (fd) to the list of clients.
 * @param setDevMode Specify the DevMode status.
 * @param getMaxSize Retrieve the maximum packet size allowed for clients.
 * @param get_CGI Retrieve the CGI Program currently configured for handling the CGI scripts.
 * @param get_CGI_Ext Retrieve the CGI extention.
 * @param use_CGI Check if the system is configured to handle CGI.
 * @param getLogPath Retrieve the location of the log file.
 * @param getLogStream Provides a stream for writing to the log file.
 * @param getSockets Retrieve a list containing the file descriptors (fds) of the sockets.
 * @param getNetworkFDs Gets the list of network clients' file descriptors.
 * @param getClientIP Gets the client IP address from the network file descriptor.
 * @param deleteClient Erase a client from the active connections.
 * @param DevMode Check the status of DevMode.
 *
 */
class SysData
{
	private:
		size_t			_maxBodySize;

		std::string		_LogPath;
		std::fstream	_LogFile;

		std::string		_CGI;
		std::string		_CGI_Ext;
		bool			_UseCGI;

		bool			_DevMode;
		std::set<int>				sockets;
		std::vector<pollfd>			networkFDs;
		std::map<int, std::string>	clientIP;
		std::map<int, RequestData *>	Requests;
		std::map<int, ResponseData *>	Responses;
	public:

		/**
		 * @brief Initialize the system data with default values.
		 */
		SysData(void);
		~SysData(void);

		/**
		 * @brief Define the maximum size, in bytes, for packets that the client can transmit.
		 * 
		 * @param newSize New size in bytes.
		 */
		void	setMaxBodySize(const size_t newSize);

		/**
		 * @brief Set the log file to be utilized by the system.
		 * 
		 * @param newLogPath The path of the new log file.
		 */
		void	setLogPath(const std::string &newLogPath);

		/**
		 * @brief Specify the CGI program.
		 * 
		 * @param  CGI_Program Program for executing the scripts.
		 */
		void	set_CGI(const std::string &CGI_Program);

		/**
		 * @brief Specify the CGI extention.
		 * 
		 * @param CGI_Extention Extension used for CGI scripts.
		 */
		void	set_CGI_Ext(const std::string &CGI_Extention);

		/**
		 * @brief Append a socket file descriptor (fd) to the list of sockets.
		 * 
		 * @param socketFd Socket file descriptor.
		 */
		void	addSocket(int socketFd);

		/**
		 * @brief Append a client file descriptor (fd) to the list of clients.
		 * 
		 * @param socketFd Client file descriptor.
		 */
		void	addClient(int clientFd, const std::string &clientIP);

		/**
		 * @brief Set the DevMode.
		 * 
		 * @param status DevMode new status.
		 */
		void	setDevMode(bool status);

		/**
		 * @brief Retrieve the maximum packet size allowed for clients.
		 * 
		 * @return size_t The maximum allowed size, in bytes.
		 */
		size_t	getMaxSize(void) const;

		/**
		 * @brief Check if the system is configured to handle CGI.
		 * 
		 * @return Status of CGI configuration.
		 */
		bool	use_CGI(void) const;

		/**
		 * @brief Retrieve the CGI Program currently configured for handling the CGI scripts.
		 * 
		 * @return const std::string& The CGI Program to use.
		 */
		const std::string	&get_CGI(void) const;

		/**
		 * @brief Retrieve the CGI extension currently configured for handling in the system.
		 * 
		 * @return const std::string& The CGI extension currently being handled by the system.
		 */
		const std::string	&get_CGI_Ext(void) const;

		/**
		 * @brief Retrieve the location of the log file.
		 * 
		 * @return const std::string& The path of the current log file.
		 */
		const std::string 	&getLogPath(void) const;

		/**
		 * @brief Provides a stream for writing to the log file.
		 * 
		 * @return std::fstream& Reference to the stream.
		 */
		std::ostream		&getLogStream(void);

		/**
		 * @brief Gets the list of socket file descriptors.
		 * 
		 * @return const std::vector<int>& Reference to the list of socket file descriptors.
		 */
		std::set<int>		&getSockets(void);

		/**
		 * @brief Gets the list of network clients' file descriptors.
		 * 
		 * @return std::vector<pollfd>& Reference to the list of network clients' file descriptors.
		 */
		std::vector<pollfd>	&getNetworkFDs(void);

		/**
		 * @brief Gets the client IP address from the network file descriptor.
		 * 
		 * @param fd The network file descriptor.
		 * @return const std::string The client IP address.
		 */
		const std::string	getClientIP(int fd);

		/**
		 * @brief Erase a client from the active connections.
		 * 
		 * @param clientfd The client network file descriptor.
		 */
		void	deleteClient(int clientfd);

		/**
		 * @brief Check the DevMode status.
		 * 
		 * @return Status of The DevMode.
		 */
		bool	DevMode(void) const;

		/**
		 * @brief Gets the request packets for each connection file descriptor.
		 * 
		 * @return std::map<int, RequestData *>& Reference to the list of request packets.
		 */
		std::map<int, RequestData *>	&getRequestPackets(void);

		/**
		 * @brief Gets the response packets for each connection file descriptor.
		 * 
		 * @return std::map<int, ResponseData *>& Reference to the list of response packets.
		 */
		std::map<int, ResponseData *>	&getResponsePackets(void);
};

#endif