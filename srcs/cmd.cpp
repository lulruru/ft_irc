/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rencarna <rencarna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:30:35 by russelenc         #+#    #+#             */
/*   Updated: 2024/04/22 14:50:10 by rencarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"

int Server::cmd_used_name(std::string &name, int mode){
	if(mode == 1){
		for(std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
		{
			if(name == it->second.getClientUserName())
				return (1);
		}
	}
	if(mode == 0){
		for(std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
		{
			if(name == it->second.getClientNickName())
				return (1);
		}
	}
	return(0);
}

void Server::cmd_user(std::vector<std::string> command, int fd){
	std::vector<std::string>::iterator it = command.begin();
	std::string err = "localhost";
	std::cout << "test" << std::endl;
	if(command.size() < 2)
	{
		std::string tmp = "USER";
		send_rpl(ERR_NOTENOUGHPARAM(tmp), fd);
		return ;
	}
	if(_clients[fd].getClientPass() == false)
		send_rpl(ERR_NOTREGISTERED(err), fd);
	else if(*(it + 1) == "")
		send_rpl(ERR_NOTENOUGHPARAM(err), fd);
	else if(cmd_used_name(*(it + 1), 1))
		send_rpl(ERR_ALREADYREGISTERED(err), fd);
	else if((*(it + 1))[0] == '#')
		send_rpl(ERR_ERRONEUSNICK(err), fd);
	else{
		std::cout << "new fct " <<*(it+1) << std::endl;
		_clients[fd].setClientUsername(*(it + 1));
		send_rpl(RPL_CONNECTED(_clients[fd].getClientUserName()), fd);
	}
}

void Server::cmd_nick(std::vector<std::string> command, int fd){
	std::vector<std::string>::iterator it = command.begin();
	std::string err = "localhost";
	// std::cout << "test" << std::endl;
	if(command.size() < 2)
	{
		std::string tmp = "USER";
		send_rpl(ERR_NOTENOUGHPARAM(tmp), fd);
		return ;
	}
	if(_clients[fd].getClientPass() == false)
		send_rpl(ERR_NOTREGISTERED(err), fd);
	else if(*(it + 1) == "")
		send_rpl(ERR_NOTENOUGHPARAM(err), fd);
	else if(cmd_used_name(*(it + 1), 1))
		send_rpl(ERR_ALREADYREGISTERED(err), fd);
	else if((*(it + 1))[0] == '#')
		send_rpl(ERR_ERRONEUSNICK(err), fd);
	else{
		_clients[fd].setClientNickname(*(it + 1));
	}
}

// void Server::cmd_pass(std::vector<std::string> command, int fd){
	
// }