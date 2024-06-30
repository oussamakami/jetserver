/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:54:20 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 13:44:24 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_HPP
# define TOOLS_HPP

# include <cstdarg>
# include <cstdlib>
# include <csignal>
# include <vector>
# include <algorithm>
# include "../classes/classes.hpp"

class ResponseData;


/**
 * @brief Print a notification message to a stream.
 * with custom formatting flags:
 * 
 * @note %%  = The Character '%'.
 * @note %c  = Character argument.
 * @note %s  = String argument.
 * @note %d  = Integer argument.
 * @note %I  = INFO (in blue).
 * @note %W  = WARNING (in yellow).
 * @note %E  = ERROR (in red).
 * 
 * @param outStream Stream specifying the destination for the notification.
 * @param format The notificiation message format string.
 * @param ... Arguments to be formatted and printed.
 */
void	notify(std::ostream &outStream, std::string format, ...);

/**
 * @brief Trims the characters specified in charList from the beginning and end of the input string.
 * 
 * @param str The input string to be trimmed.
 * @param charList A string containing the characters to be trimmed.
 * @return std::string The trimmed string.
 */
std::string trim(const std::string &str, const std::string &charList);

/**
 * @brief Splits a string into a vector of substrings using the specified delimiter.
 * 
 * @param str The input string to be split.
 * @param delimiter The delimiter used to split the string.
 * @return std::vector<std::string> A vector containing the substrings.
 */
std::vector<std::string> split(const std::string &str, const std::string &delimiter);

/**
 * @brief Terminates the program with the specified error code after freeing the global namespace.
 * 
 * @param errorCode The error code to be used for program termination.
 */
void	terminate(unsigned char errorCode);

/**
 * @brief Terminates the program and releases the global namespace upon receiving a SIGINT or SIGTERM signal.
 * 
 */
void	terminateOnSignal(void);

/**
 * @brief Checks if a specified path exists in the filesystem.
 * 
 * @param fullPath The full system path to check.
 * @return true if the path exists, false otherwise.
 */
bool	doesExist(const std::string &fullPath);

/**
 * @brief Checks if the specified path is a folder.
 * 
 * @param fullPath The full system path to check.
 * @return true if the path is a folder, false otherwise.
 */
bool	isFolder(const std::string &fullPath);

/**
 * @brief Checks if the specified path is a CGI script.
 * 
 * @param fullPath The full system path to check.
 * @return true if the path is a CGI script, false otherwise.
 */
bool	isCGI(const std::string &fullPath);

/**
 * @brief Writes network communication details to the log file.
 * 
 * @param Packet Reference to the response HTTP packet.
 */
void	captureLog(ResponseData &Packet);

/**
 * @brief Converts a string to an integer.
 * 
 * @param num The string representing the number.
 * @return int The integer value of the string.
 */
int			StringToInt(const std::string &num);

/**
 * @brief Converts an integer to a string.
 * 
 * @param num The integer to convert.
 * @return std::string The string representation of the number.
 */
std::string	intToString(int num);

/**
 * @brief Generates a list of combinations of parent paths from the given path.
 * 
 * @param path The path to process.
 * @return std::vector<std::string> A list of the given path and its parent directories.
 */
std::vector<std::string>	pathCombs(const std::string &path);

/**
 * @brief Retrieves the content of a directory.
 * 
 * @param DirPath The full system path to the directory.
 * @return std::vector<std::string> A list containing all the files and subfolders in the directory.
 */
std::vector<std::string>	getDirContent(const std::string &DirPath);

/**
 * @brief Generates an HTML page containing an autoindex of a directory.
 * 
 * @param DirPath The full system path to the directory.
 * @param RequestPath The HTTP request path.
 * @return std::string The HTML code for autoindexing the directory.
 */
std::string		generateDirPage(const std::string &DirPath, const std::string &RequestPath);

/**
 * @brief Retrieves the index file from a directory based on route rules.
 * 
 * @param DirPath The full system path to the directory.
 * @param route Pointer to the route rules for the directory path.
 * @return std::string The index file name or an empty string if no index file is found.
 */
std::string		getIndexFile(const std::string &DirPath, const Locations *route);

#endif