/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Locations.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 05:17:56 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 13:16:41 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONS_HPP
# define LOCATIONS_HPP

# include <iostream>
# include <set>

/**
 * @brief Class for holding route data and configurations.
 * 
 * @param setPath Set the HTTP request packet path for this route.
 * @param setRoot Set the root path for this route.
 * @param addIndex Add an index file to the list of default index files.
 * @param setMethod Set the status of supported HTTP methods for this route.
 * @param setBrowsing Set the auto indexing status for this route.
 * @param setRedirection Set a redirection URL or Path for HTTP requests related to this route.
 * @param setRedirectionType Set the type of redirection for this route.
 * @param getPath Get the HTTP packet path related to this route.
 * @param getRoot Get the root path related to this route.
 * @param getRedirection Get the redirection URL.
 * @param isRedirection Check if this route redirects requests.
 * @param isRedirectionHard Check if the redirection type of this route is hard.
 * @param autoindex Check if this route supports auto indexing.
 * @param useMethod Check if this route supports an HTTP method.
 * @param isIndex Check if a file name is an index for this route.
 * @param getIndexes Get the list of index file names.
 * 
 */
class Locations
{
	private:
		std::string					_PathReq;
		std::string					_Root;
		std::set<std::string>		_Index;
		bool						_UseGet;
		bool						_UsePost;
		bool						_UseDelete;
		bool						_BrowsDir;
		bool						_isRedirect;
		bool						_HardRedirection;
		std::string					_Redirection;
	public:

		/**
		 * @brief Initialize the Locations class.
		 * 
		 * @param sysDevMode The status of dev mode.
		 */
		Locations(bool sysDevMode);
		~Locations(void);

		/**
		 * @brief Set the HTTP request packet path for this route.
		 * 
		 * @param Path The HTTP packet path.
		 */
		void	setPath(const std::string &Path);

		/**
		 * @brief Set the root path for this route.
		 * 
		 * @param Root The root path.
		 */
		void	setRoot(const std::string &Root);

		/**
		 * @brief Add an index file to the list of default index files.
		 * 
		 * @param Index The name of the index file to add.
		 */
		void	addIndex(const std::string &Index);

		/**
		 * @brief Set the status of supported HTTP methods for this route.
		 * 
		 * @param methodName The method name (e.g., "get", "post", "delete").
		 * @param status True if the method is supported, false otherwise.
		 * @return True if the changes were applied successfully, false otherwise.
		 */
		bool	setMethod(const std::string &methodName, bool status);

		/**
		 * @brief Set the auto indexing status for this route.
		 * 
		 * @param status True to enable auto indexing, false to disable.
		 */
		void	setBrowsing(bool status);

		/**
		 * @brief Set a redirection URL or Path for HTTP requests related to this route.
		 * 
		 * @param redirectionUrl The URL or Path to redirect requests to.
		 */
		void	setRedirection(const std::string &redirectionUrl);

		/**
		 * @brief Set the type of redirection for this route.
		 * 
		 * @param redirectionType "hard" for hard redirection, "soft" for soft redirection.
		 * @return True if the changes were applied successfully, false otherwise.
		 */
		bool	setRedirectionType(const std::string &redirectionType);

		/**
		 * @brief Get the HTTP packet path related to this route.
		 * 
		 * @return const std::string& Reference to the HTTP packet path.
		 */
		const std::string	&getPath(void) const;

		/**
		 * @brief Get the root path related to this route.
		 * 
		 * @return const std::string& Reference to the root path.
		 */
		const std::string	&getRoot(void) const;

		/**
		 * @brief Get the redirection URL.
		 * 
		 * @return const std::string& Reference to the redirection URL.
		 */
		const std::string	&getRedirection(void) const;

		/**
		 * @brief Check if this route redirects requests.
		 * 
		 * @return true if the route redirects requests, 
		 */
		bool				isRedirection(void) const;

		/**
		 * @brief Check if the redirection type of this route is hard.
		 * 
		 * @return true if hard redirection is used, false otherwise.
		 */
		bool				isRedirectionHard(void) const;

		/**
		 * @brief Check if this route supports auto indexing.
		 * 
		 * @return true if auto indexing is supported, false otherwise.
		 */
		bool				autoIndex(void) const;

		/**
		 * @brief Check if this route supports an HTTP method.
		 * 
		 * @param methodName The HTTP method name (e.g., "get", "post", "delete").
		 * @return true if the method is supported, false otherwise.
		 */
		bool				useMethod(const std::string &methodName) const;

		/**
		 * @brief Check if a file name is an index for this route.
		 * 
		 * @param fileName The file name to check.
		 * @return true if the file is an index, false otherwise.
		 */
		bool				isIndex(const std::string &fileName) const;

		/**
		 * @brief Get the list of index file names.
		 * 
		 * @return const std::set<std::string>& Reference to the list of index file names.
		 */
		const std::set<std::string>	&getIndexs(void) const;
};

#endif