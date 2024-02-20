/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SysData.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 03:26:09 by okamili           #+#    #+#             */
/*   Updated: 2024/02/20 04:24:34 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSDATA_HPP
# define SYSDATA_HPP

# include <iostream>
# include <fstream>


/**
 * @brief This class encapsulates system configuration settings
 * related to the log file, CGI, etc...
 * 
 * @param setMaxBodySize Define the maximum size, in bytes, for packets that the client can transmit.
 * @param setLogPath Specify the log file to be utilized by the system.
 * @param setCGI Specify the CGI extension to handle.
 * @param setDevMode Specify the DevMode status.
 * @param getMaxSize Retrieve the maximum packet size allowed for clients.
 * @param get_CGI Retrieve the CGI Program currently configured for handling the CGI scripts.
 * @param get_CGI_Ext Retrieve the CGI extention.
 * @param use_CGI Check if the system is configured to handle CGI.
 * @param getLogPath Retrieve the location of the log file.
 * @param getLogStream Provides a stream for writing to the log file.
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
		 * @brief Specify the CGI extension to handle.
		 * 
		 * @param newCGI CGI program for executing the scripts.
		 * @param CGI_Extention Extension used for CGI scripts.
		 */
		void	setCGI(const std::string &CGI_Program, const std::string &CGI_Extention);
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
		 * @return status of CGI configuration.
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
		 * @return std::fstream& A reference to the stream.
		 */
		std::fstream		&getLogStream(void);
		/**
		 * @brief Check the DevMode status.
		 * 
		 * @return status of The DevMode.
		 */
		bool	DevMode(void) const;
};

#endif
