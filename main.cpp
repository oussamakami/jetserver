/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 03:50:48 by okamili           #+#    #+#             */
/*   Updated: 2024/02/25 09:07:08 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "classes/classes.hpp"

SysData	*global::system = new SysData();

int main(int argc, char **argv)
{
	if (argc > 2)
		return (2);
	if (argc == 2)
		return (1);
		
	std::cout << global::system->getLogPath() << "\n";
	return (0);
}
