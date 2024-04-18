/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: russelenc <russelenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:24:53 by russelenc          #+#    #+#             */
/*   Updated: 2024/03/23 19:24:53 by russelenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
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

enum{
	PASS,
	NICK,
	USER
};

class Client
{
	public:

	// Constructeurs & Destructeurs
    Client();
    Client(Client const &src);
    ~Client();

	// Surcharge d'opérateurs
    Client& operator=(Client const &rhs);

	// Getters & Setters
	int GetFd(){return _fd;}
	void setFd(int fd){_fd = fd;}
	void setIpAdd(std::string ipadd){_IPadd = ipadd;}
	void setClientRegistrated(){_registrated = true;}
	void setClientUsername(std::string name){username = name;}
	void setClientNickname(std::string name){nickname = name;}
	void setClientPass(){_pass = true;}
	void SetIncrementInfo(){_info++;}
	void setRegistrated(){_registrated = true;}

	int getNumberInfo(){return this->_info;}
	bool getClientPass(){return this->_pass;}
	std::string getClientUserName(){return this->username;}
	std::string getClientNickName(){return this->nickname;}
	bool getClientRegistratedInfo(){return this->_registrated;}
	// Méthodes
	void parser();
	
	private:
	int _fd;
	std::string _IPadd;
	bool _pass;
	bool _registrated;
	std::string username;
	std::string nickname;
	int _info;
};

