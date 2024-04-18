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
#include "ErrorMessage.hpp"

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
	
	// Méthodes
	void InitServ(char *port, std::string password);
	void SocketCreator();
	void NewClientAccept();
 	void ReceiveData(int fd);
	// void parsing_data(int fd);
	static void SignalHandler(int signum);
	void registration(int fd, std::string buff);
	void CloseFds();
	void ClearClients(int fd);

	private:
	static bool _lock;
	int _port;
	std::string _password;
	int _fdSocket;
	static bool _signal;
	std::vector<Client> _clients;
	std::vector<struct pollfd> _fds;
};