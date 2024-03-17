/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Locations.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 05:17:56 by okamili           #+#    #+#             */
/*   Updated: 2024/03/17 06:12:04 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONS_HPP
# define LOCATIONS_HPP

# include <iostream>
# include <set>

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
		std::string					_Redirection;
	public:
		Locations(bool sysDevMode);
		~Locations(void);
		void	setPath(const std::string &Path);
		void	setRoot(const std::string &Root);
		void	addIndex(const std::string &Index);
		bool	setMethod(const std::string &methodName, bool status);
		void	setBrowsing(bool status);
		void	setRedirection(const std::string &redirectionUrl);

		const std::string	&getPath(void) const;
		const std::string	&getRoot(void) const;
		const std::string	&getRedirection(void) const;
		bool				isRedirection(void) const;
		bool				useMethod(const std::string &methodName) const;
		bool				isIndex(const std::string &fileName) const;
		const std::set<std::string>	&getIndexs(void) const;
};

#endif
