/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 09:16:11 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 11:45:06 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
# define PARSING_HPP

# include "../tools/tools.hpp"

/**
 * @brief Checks if the given file path corresponds to a configuration file.
 * 
 * @param path The path to the file to be checked.
 * @return true if the file is a configuration file, false otherwise.
 */
bool	isConfigFile(const std::string &path);

/**
 * @brief Checks if a file exists at the specified path.
 * 
 * @param path The path to the file to be checked.
 * @return true if the file exists, false otherwise.
 */
bool	fileExist(const std::string &path);

/**
 * @brief Checks if an option has only one value set.
 * 
 * @param optionName The name of the option to check.
 * @param Value The value of the option.
 * @param fileLine The line number in the configuration file.
 * @return true if the option has only one value, false otherwise.
 */
bool hasOneValue(const std::string &optionName, const std::string &Value, size_t &fileLine);

/**
 * @brief Extracts an option and its value from a string based on a separator.
 * 
 * @param trimedStr The trimmed string containing the option and value.
 * @param sep The separator used to separate the option and value.
 * @return std::vector<std::string> A vector containing the option and value as separate elements.
 */
std::vector<std::string> extractOption(const std::string &trimedStr, const std::string &sep);

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

/**
 * @brief Extract servers configuration from the provided input stream
 * 		  and load it into the global namespace.
 * 
 * @param source The input file stream to read from.
 * @param fileLine The current line number in the file being processed.
 * @return true if the servers configuration was successfully extracted and loaded,
 * 		   false otherwise.
 */
bool	parseServers(std::ifstream &source, size_t &fileLine);

/**
 * @brief Extract routes configuration from the provided input stream
 * 		  and load it into the servers from the global namespace.
 * 
 * @param source The input file stream to read from.
 * @param fileLine The current line number in the file being processed.
 * @return true if the extraction was successfull, false otherwise.
 */
bool	parseRoutes(std::ifstream &source, size_t &fileLine);

/**
 * @brief Loads the configuration from the specified file into the global namespace.
 * 
 * @param confPath The path to the configuration file.
 * @return true if the configuration was successfully loaded, false otherwise.
 */
bool	loadConfig(std::string confPath);

#endif