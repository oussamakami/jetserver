/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseData.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:11:32 by okamili           #+#    #+#             */
/*   Updated: 2024/06/10 13:12:44 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEDATA_HPP
# define RESPONSEDATA_HPP

# include "../RequestData/RequestData.hpp"
# include "../../tools/tools.hpp"
# include <ctime>

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
		ResponseData(void);
		~ResponseData(void);
		bool		setStatusCode(int statusCode);
		bool		setMetaData(const std::string &key, const std::string &value);
		bool		setBody(const std::string &data);
		bool		isBusy(void);
		bool		sendResponse(int fd);
		bool		redirect(const std::string &Path, bool isHard);
		void		setRequestPacket(RequestData &Packet);
		RequestData	*getRequestPacket(void);
	
		bool	readFile(const std::string &Path);
};

#endif