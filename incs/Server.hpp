/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: russelenc <russelenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:24:48 by russelenc          #+#    #+#             */
/*   Updated: 2024/03/23 19:24:48 by russelenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <iostream>
#include <vector> //-> for vector
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl()
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <poll.h> //-> for poll()
#include <csignal> //-> for signal()
#include "Client.hpp"
#include <cstring>
#include <stdlib.h> 
#include <iostream>
#include <string>
#include <sstream>
#include "rpl.hpp"
#include "map"




class Server
{
	public:

	// Constructeurs & Destructeurs
    Server();
    Server(Server const &src);
    ~Server();

	// Surcharge d'opérateurs
    Server& operator=(Server const &rhs);

	// Getters & Setters
	typedef void (Server::*ptr_cmd_func)(std::vector<std::string>, int);
	// Méthodes
	void InitServ(char *port, std::string password);
	void SocketCreator();
	void NewClientAccept();
 	void ReceiveData(int fd);
	// void parsing_data(int fd);
	static void SignalHandler(int signum);
	void handle_cmd(int fd, std::string buff);
	void CloseFds();
	void ClearClients(int fd);

	//COMMAND HANDLER
	void cmd_user(std::vector<std::string> command, int fd);
	void cmd_nick(std::vector<std::string> command, int fd);
	void cmd_pass(std::vector<std::string> command, int fd);
	int cmd_used_name(std::string &name, int mode);

	void send_rpl(std::string rpl, int fd);

	private:
	static bool _lock;
	int _port;
	std::string _password;
	int _fdSocket;
	static bool _signal;
	std::map<int, Client> _clients;
	std::map<std::string, ptr_cmd_func> cmd_map;
	std::vector<struct pollfd> _fds;
};
