/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Locations.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 05:17:56 by okamili           #+#    #+#             */
/*   Updated: 2024/02/29 09:20:10 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONS_HPP
# define LOCATIONS_HPP

# include <iostream>
# include <vector>

class Locations
{
	private:
		std::string					_PathReq;
		std::string					_Root;
		std::vector<std::string>	*_Index;
		bool						_UseGet;
		bool						_UsePost;
		bool						_UseDelete;
		bool						_BrowsDir;
		bool						_isRedirect;
		std::string					_Redirection;
		Locations					*_Prev;
		Locations					*_Next;
	public:
		Locations(bool sysDevMode);
		~Locations(void);
		void	setPath(const std::string &Path);
		void	setRoot(const std::string &Root);
		void	addIndex(const std::string &Index);
		void	setMethod(const std::string &methodName, bool status);
		void	setBrowsing(bool status);
		void	setRedirection(const std::string &redirectionUrl);
		void	setNext(Locations *nextRoute);

		const std::string	&getPath(void) const;
		const std::string	&getRoot(void) const;
		const std::string	&getRedirection(void) const;
		bool				isRedirection(void) const;
		bool				useMethod(const std::string &methodName) const;
		Locations			*getNext(void);
		Locations			*getPrev(void);
		bool				isIndex(const std::string &fileName) const;
};

#endif
