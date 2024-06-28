/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseData.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:46:47 by okamili           #+#    #+#             */
/*   Updated: 2024/06/27 07:07:42 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ResponseData.hpp"
# include <sys/socket.h>

bool	ResponseData::_LoadMimeTypes(void)
{
	std::ifstream				file;
	std::string					line;
	std::vector<std::string>	temp;
	
	file.open("./classes/ResponseData/Mime.type");

	if (!file.is_open())
		return (false);
	while (getline(file, line))
	{
		temp = split(line, " = ");
		_MimeTypes[trim(temp.at(0), " ")] = trim(temp.at(1), " ");
	}
	file.close();
	return (true);
}

bool	ResponseData::_LoadStatusTypes(void)
{
	std::ifstream				file;
	std::string					line;
	std::vector<std::string>	temp;
	
	file.open("./classes/ResponseData/HttpStatus.txt");

	if (!file.is_open())
		return (false);
	while (getline(file, line))
	{
		temp = split(line, " = ");
		_StatusTypes[StringToInt(trim(temp.at(0), " "))] = trim(temp.at(1), " ");
	}
	return (true);
}

std::string	ResponseData::_GetPacketDate(void)
{
	time_t		time = std::time(NULL);
	std::tm 	date = *std::gmtime(&time);
	std::string	daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	std::string	monthsOfYear[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	std::stringstream	result;

	result << daysOfWeek[date.tm_wday] << ", ";
	result << (date.tm_mday < 10 ? "0" : "") << date.tm_mday << " ";
	result << monthsOfYear[date.tm_mon] << " ";
	result << (date.tm_year + 1900) << " ";
	result << (date.tm_hour < 10 ? "0" : "") << date.tm_hour << ":";
	result << (date.tm_min < 10 ? "0" : "") << date.tm_min << ":";
	result << (date.tm_sec < 10 ? "0" : "") << date.tm_sec << " GMT";
	
	return (result.str());
}

std::string	ResponseData::_GetFileType(const std::string &filePath)
{
	std::string	fileExtention;

	if (filePath.empty())
		return ("text/html");

	fileExtention = split(filePath, ".").back();
	if (_MimeTypes.find(fileExtention) != _MimeTypes.end())
		return (_MimeTypes.find(fileExtention)->second);
	return ("application/octet-stream");
}

void	ResponseData::_GenerateHead(void)
{
	std::map<std::string, std::string>::iterator it;

	_Head = "HTTP/1.1 ";
	_Head += _StatusCode;
	_Head += "\r\nDate: ";
	_Head += _GetPacketDate();
	_Head += "\r\n";

	for (it = _MetaData.begin(); it != _MetaData.end(); it++)
	{
		_Head += it->first;
		_Head += ": ";
		_Head += it->second;
		_Head += "\r\n";
	}
	_Head += "\r\n";
}

bool	ResponseData::isBusy(void)
{
	return (!_Packet.empty());
}

bool	ResponseData::setBody(const std::string &data)
{
	if (data.empty())
		return (false);
	_Body = data;
	setMetaData("Content-Length", intToString(_Body.length()));
	return (true);
}

bool	ResponseData::setMetaData(const std::string &key, const std::string &value)
{
	if (key.empty() || value.empty())
		return (false);
	_MetaData[key] = value;
	return (true);
}

bool	ResponseData::_GeneratePacket(void)
{
	if (_Head.empty())
		return (false);
	_Packet += _Head;
	_Packet += _Body;
	return (true);
}

bool	ResponseData::redirect(const std::string &Path, bool isHard)
{
	if (Path.empty())
		return (false);

	if (isHard)
		setStatusCode(301);
	else
		setStatusCode(307);

	setMetaData("Location", Path);
	setMetaData("Content-Length", "0");
	setMetaData("Connection", "close");
	return (true);
}

bool	ResponseData::setStatusCode(int statusCode)
{
	std::map<int, std::string>::iterator	holder;

	holder = _StatusTypes.find(statusCode);

	if (holder == _StatusTypes.end())
	{
		_StatusCode = "500 Internal Server Error";
		if (_requestPacket && _requestPacket->getServer())
			_Body = _requestPacket->getServer()->getError(statusCode, "Internal Server Error");
		else
			_Body = global::servers->at(0)->getError(statusCode, "Internal Server Error");
		return (false);
	}

	_StatusCode = intToString(statusCode);
	_StatusCode += " ";
	_StatusCode += holder->second;

	if (statusCode >= 400)
	{
		if (_requestPacket && _requestPacket->getServer())
			_Body = _requestPacket->getServer()->getError(statusCode, holder->second);
		else
			_Body = global::servers->at(0)->getError(statusCode, holder->second);
	}

	return (true);
}

bool	ResponseData::readFile(const std::string &path)
{
	std::fstream		fileStream;
	int					bytesRead = 0;
	char				buffer[2048];

	if (path.empty())
			return (false);

	if (!fileStream.is_open())
	{
		fileStream.open(path.c_str(), std::ios::in | std::ios::binary);
		fileStream.seekg(0, std::ios_base::end);
		bytesRead = fileStream.tellg();
		fileStream.seekg(0, std::ios_base::beg);
		setMetaData("Content-Length", intToString(bytesRead));
		setMetaData("Content-Type", _GetFileType(path));
		setBody("");
		bytesRead = 0;
	}
	fileStream.read(buffer, 2048);
	bytesRead = fileStream.gcount();
	while (bytesRead == 2048)
	{
		_Body.append(buffer, bytesRead);
		fileStream.read(buffer, 2048);
		bytesRead = fileStream.gcount();
	}
	_Body.append(buffer, bytesRead);
	fileStream.close();
	return (true);
}

bool	ResponseData::sendResponse(int fd)
{
	size_t		bufferSize = 1024;
	std::string	response;

	if (!isBusy())
	{
		_GenerateHead();
		if (!_GeneratePacket())
			return (false);
	}
	response = _Packet.substr(0, bufferSize);
	if (send(fd, response.c_str(), response.length(), 0) == -1)
	{
		_Packet = "";
		return (false);
	}
	_Packet.erase(0, bufferSize);
	return (true);
}

ResponseData::ResponseData(void)
{
	if (!_LoadMimeTypes())
	{
		notify(std::cerr, "%EFailed to load mime types.");
		terminate(1);
	}

	if (!_LoadStatusTypes())
	{
		notify(std::cerr, "%EFailed to load HTTP status types.");
		terminate(1);
	}

	_StatusCode = "200 OK";
	_Head = "";
	_Body = "";
	_Packet = "";
	_requestPacket = NULL;
	setMetaData("Server", "webServer/1.0");
}

ResponseData::~ResponseData(void)
{
	
}

void	ResponseData::setRequestPacket(RequestData &Packet)
{
	_requestPacket = &Packet;
}

RequestData	*ResponseData::getRequestPacket(void)
{
	return (this->_requestPacket);
}