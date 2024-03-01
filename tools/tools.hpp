/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:54:20 by okamili           #+#    #+#             */
/*   Updated: 2024/03/01 12:42:05 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_HPP
# define TOOLS_HPP

# include "../classes/classes.hpp"
# include <cstdarg>
# include <cstdlib>
# include <vector>

/**
 * @brief Print a notification message to a stream.
 * with custom formatting flags:
 * 
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

#endif
