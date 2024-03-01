/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 09:16:11 by okamili           #+#    #+#             */
/*   Updated: 2024/03/01 10:32:24 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
# define PARSING_HPP

# include "../tools/tools.hpp"
# include "sstream"

/**
 * @brief Checks if the given file path corresponds to a configuration file.
 * 
 * @param path The path to the file to be checked.
 * @return true if the file is a configuration file, false otherwise.
 */
bool	isConfigFile(std::string path);

/**
 * @brief Checks if a file exists at the specified path.
 * 
 * @param path The path to the file to be checked.
 * @return true if the file exists, false otherwise.
 */
bool	fileExist(std::string path);


std::vector<std::string> extractOption(const std::string &holder, const std::string &sep);

/**
 * @brief Extract system configuration from the provided input stream
 * 		  and load it into the global namespace.
 * 
 * @param source The input file stream to read from.
 * @param fileLine The current line number in the file being processed.
 * @return true if the system configuration was successfully extracted and loaded,
 * 		   false otherwise.
 */
bool	parseSystem(std::ifstream &source, size_t &fileLine);

bool	parseServers(std::ifstream &source, size_t &fileLine);
bool	loadConfig(std::string confPath);


#endif
