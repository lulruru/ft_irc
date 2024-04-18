/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: russelenc <russelenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:24:48 by russelenc          #+#    #+#             */
/*   Updated: 2024/03/23 19:24:48 by russelenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"

int	main(int ac, char **av)
{
	Server server;
	try{
		if(ac != 3)
			throw(std::runtime_error("Not enough arg"));
		signal(SIGINT, Server::SignalHandler); //-> catch the signal (ctrl + c)
  		signal(SIGQUIT, Server::SignalHandler); //-> catch the signal (ctrl + \)
		server.InitServ(av[1], av[2]);
	}
	catch(const std::exception &e){
		server.CloseFds();
		std::cout << e.what() << std::endl;
	}
	return (0);
}


