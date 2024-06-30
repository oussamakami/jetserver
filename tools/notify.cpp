/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notify.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 09:17:00 by okamili           #+#    #+#             */
/*   Updated: 2024/06/30 12:02:34 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

static void	typeHandler(std::ostream &outStream, char type, va_list args)
{
	if (type == 'c' || type == 'd')
		outStream << va_arg(args, int);
	else if (type == 's')
		outStream << va_arg(args, char *);
	else if (type == 'W')
		outStream << "\033[1;33mWARNING\033[1;0m: ";
	else if (type == 'I')
		outStream << "\033[1;34mINFO\033[1;0m: ";
	else if (type == 'E')
		outStream << "\033[1;31mERROR\033[1;0m: ";
	else if (type == '%')
		outStream << '%';
}

void	notify(std::ostream &outStream, std::string format, ...)
{
	va_list	args;
	va_start(args, format);
	for (int i = 0; format[i]; i++)
	{
		if (format[i] == '%')
			typeHandler(outStream, format[++i], args);
		else
			outStream << format[i];
	}
	outStream << "\n";
	va_end(args);
	outStream.flush();
}