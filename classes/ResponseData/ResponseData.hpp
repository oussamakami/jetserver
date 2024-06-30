/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseData.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:11:32 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 13:18:35 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEDATA_HPP
# define RESPONSEDATA_HPP

# include "../RequestData/RequestData.hpp"
# include "../../tools/tools.hpp"
# include <ctime>

/**
 * @brief Class for managing and sending HTTP response packets.
 * 
 * @param getStatusCode Get the HTTP status code of the response.
 * @param setStatusCode Sets the HTTP status code for the response.
 * @param setMetaData Sets metadata for the HTTP response.
 * @param setBody Sets the body of the HTTP response.
 * @param isBusy Checks if the class is currently busy sending a packet response.
 * @param sendResponse Sends the HTTP response packet to the client.
 * @param redirect Sets the packet to redirect the client.
 * @param setRequestPacket Sets the HTTP request packet.
 * @param getRequestPacket Retrieves the HTTP request packet.
 * @param readFile Loads file data into the response packet and sets appropriate metadata.
 * 
 */
class ResponseData
{
	private:
		RequestData							*_requestPacket;
	
		std::string							_StatusCode;
		std::map<std::string, std::string>	_MetaData;

		std::string							_Head;
		std::string							_Body;
		std::string							_Packet;

		std::map<int, std::string>			_StatusTypes;
		std::map<std::string, std::string>	_MimeTypes;
		bool								_LoadMimeTypes(void);
		bool								_LoadStatusTypes(void);
		std::string							_GetPacketDate(void);
		void								_GenerateHead(void);
		bool								_GeneratePacket(void);
		std::string							_GetFileType(const std::string &filePath);
	public:

		/**
		 * @brief Constructs an empty ResponseData class.
		 */
		ResponseData(void);
		~ResponseData(void);

		/**
		 * @brief Get the HTTP status code of the response.
		 * 
		 * @return int The HTTP status code.
		 */
		int			getStatusCode(void);

		/**
		 * @brief Sets the HTTP status code for the response.
		 * 
		 * @param statusCode The HTTP status code to set.
		 * @return true if successfully set, false otherwise (defaults to 500).
		 */
		bool		setStatusCode(int statusCode);

		/**
		 * @brief Sets metadata for the HTTP response.
		 * 
		 * @param key The name of the metadata.
		 * @param value The value of the metadata.
		 * @return true if the metadata was successfully set, false otherwise.
		 */
		bool		setMetaData(const std::string &key, const std::string &value);

		/**
		 * @brief Sets the body of the HTTP response.
		 * 
		 * @param data The response data to set as the body.
		 * @return true if the body was successfully set, false otherwise.
		 */
		bool		setBody(const std::string &data);

		/**
		 * @brief Checks if the class is currently busy sending a packet response.
		 * 
		 * @return true if busy sending, false if not in use.
		 */
		bool		isBusy(void);

		/**
		 * @brief Sends the HTTP response packet to the client.
		 * 
		 * @param fd The file descriptor to the client connection.
		 * @return true on success, false on failure.
		 */
		bool		sendResponse(int fd);

		/**
		 * @brief Sets the packet to redirect the client.
		 * 
		 * @param Path Path or URL to redirect the client to.
		 * @param isHard Indicates if the redirection is hard (permanent).
		 * @return  true if the redirection packet was set successfully, false otherwise.
		 */
		bool		redirect(const std::string &Path, bool isHard);

		/**
		 * @brief Sets the HTTP request packet.
		 * 
		 * @param Packet Reference to the class containing the request data.
		 */
		void		setRequestPacket(RequestData &Packet);

		/**
		 * @brief Retrieves the HTTP request packet.
		 * 
		 * @return RequestData* Pointer to the object containing the request packet data.
		 */
		RequestData	*getRequestPacket(void);

		/**
		 * @brief Loads file data into the response packet and sets appropriate metadata.
		 * 
		 * @param Path System path to the file.
		 * @return true if the data was loaded successfully, false otherwise.
		 */
		bool	readFile(const std::string &Path);
};

#endif