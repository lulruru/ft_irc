/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: russelenc <russelenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:24:48 by russelenc          #+#    #+#             */
/*   Updated: 2024/03/23 19:24:48 by russelenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"

/* ************************************************************************** */
/*                     Constructeurs & Destructeurs                   		  */
/* ************************************************************************** */

Server::Server(){
	_fdSocket = -1;
}


Server::Server(Server const &src) {
	(void)src;
	std::cout <<  "Copy Constructor called: Server"  << std::endl;
}

Server::~Server() {

	std::cout <<  "Destructor called: Server"  << std::endl;
}

Server&	Server::operator=(Server const &rhs) {
	(void)rhs;
	std::cout <<  "Assignment Operator called: Server"  << std::endl;
	return (*this);
}

bool Server::_signal = false;

void Server::ClearClients(int fd)
{
	for(size_t i = 0 ; i < _fds.size(); i++)
		if(_fds[i].fd == fd){
			_fds.erase(_fds.begin() + i);
			break;
		}
	std::map<int, Client>::iterator it = _clients.find(fd);
    if (it != _clients.end()) {
        _clients.erase(it);
    }

}

void Server::SignalHandler(int signum)
{
	(void)signum;
	std::cout << " Signal received" << std::endl;
	_signal = true;
}

void Server::send_rpl(std::string rpl, int fd)
{
	send(fd, rpl.c_str(), rpl.size(), 0);
}

void Server::CloseFds()
{
	if(_clients.size() > 1)
	{
		for(size_t i = 0 ; i < _clients.size(); i++){
			std::cout << _clients.size() << std::endl;
				std::cout << "Client " << _clients[i].GetFd() << " is disconnected" << std::endl;
				close(_clients[i].GetFd());

		}
	}
	if (_fdSocket != -1){ //-> close the server socket
		std::cout << "Server " << _fdSocket << " is Disconnected" << std::endl;
		close(_fdSocket);
	}
}

void Server::SocketCreator(){
	//Creation de socket
	_fdSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(_fdSocket == -1)
		throw(std::runtime_error("socket creation error"));
	//Configuration de l'adresse et du port du server
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;// Famille d'adresses IPv4
	serverAddr.sin_port = htons(this->_port);//Port 
	serverAddr.sin_addr.s_addr = INADDR_ANY;// Adresse IP locale
	//Liaison du sokcket a l'adresse
	int optval = 1;
	if(setsockopt(_fdSocket, SOL_SOCKET, SO_REUSEADDR, &optval , sizeof(int)) == -1)
		throw(std::runtime_error("error on option reusaddr on socket"));

	if(fcntl(_fdSocket,F_SETFL,O_NONBLOCK) == -1)// option non bloquante sur le socket
		throw(std::runtime_error("error on option NON_BLOCK"));

	if(bind(_fdSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) //liaison entre le socket et l'adresse
		throw(std::runtime_error("error on linking address to socket"));

	if(listen(_fdSocket, SOMAXCONN) == -1) // ecoute sur le port
		throw(std::runtime_error("error on listenning on socket"));
	
	struct pollfd pollStruct;
	pollStruct.fd = _fdSocket;
	pollStruct.events = POLLIN;
	pollStruct.revents = 0;
	_fds.push_back(pollStruct);
};


void Server::NewClientAccept(){
	Client client;
	struct sockaddr_in clientAddr;
	socklen_t len = sizeof(clientAddr);
	int incofd = accept(_fdSocket, (sockaddr *)&(clientAddr), &len);
	if (incofd == -1){
		std::cout << "accept() failed" << std::endl; 
		return;
	}
	if(fcntl(incofd, F_SETFL, O_NONBLOCK) == -1){
		std::cout << "fcntl() failed" << std::endl; 
		return ;
	}
	struct pollfd pollStruct;
	pollStruct.fd = incofd;
	pollStruct.events = POLLIN;
	pollStruct.revents = 0;
	_clients.insert(std::make_pair(incofd, client));
	_clients[incofd].setRegistrated(false);
	_clients[incofd].setFd(incofd);
	_clients[incofd].setIpAdd(inet_ntoa(clientAddr.sin_addr)) ;// convertit ip adress en string
	_clients[incofd].setInfo(-1);
	std::cout <<"test " <<  _clients[incofd].GetFd() << std::endl; 
	_fds.push_back(pollStruct);
	std::cout << "Client <" << incofd << "> Connected" << std::endl;
}
// void Server::parser(){

// }


std::vector<std::string> split(const std::string& s, const std::string& delimiters) {
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;

    while ((start = s.find_first_not_of(delimiters, end)) != std::string::npos) {
        end = s.find_first_of(delimiters, start);
        tokens.push_back(s.substr(start, end - start));
    }
    return tokens;
}

void Server::registration(int fd, std::string buff)
{
	std::vector<std::string> splitted = split(buff, "\r\n");
	std::cout << splitted.size() << std::endl;
	std::vector<std::string>::iterator it = splitted.begin();
	it++;
	if (_clients[fd].getClientRegistratedInfo() == false)
		for(; it != splitted.end(); it++)
		{
			std::vector<std::string> tmp = split(*it, " ");
			std::vector<std::string>::iterator ite = tmp.begin();
			if (*ite == "PASS"){
				if (*(ite + 1) == _password){
					_clients[fd].setClientPass();
					_clients[fd].SetIncrementInfo();
				}
			}
			else if (*ite == "NICK"){
				if(_clients[fd].getClientPass() == false)
				{
					// send(fd, NoPassword.c_str() , NoPassword.size() , 0);
					return;
				}
				else{
					_clients[fd].setClientNickname(*(ite + 1));
					_clients[fd].SetIncrementInfo();
				}
			}
			else if (*ite == "USER")
				cmd_user(tmp, fd);
			else{

				std::string message = "Error : \"" + buff + "\"" + " is an unknown command. please register\r\n";
				send(fd, message.c_str(), message.size(), 0);
			}
			std::cout << *ite<< std::endl;
		}
}
void Server::ReceiveData(int fd){
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	std::string msg;
	ssize_t bytes = recv(fd, buff, sizeof(buff) -1 , 0);
	if(bytes <= 0)
	{
		std::cout << "Client <" << fd << "> Disconnected" << std::endl;
		ClearClients(fd);
		close(fd);
 	}
	else {
		buff[bytes] = '\0';
		registration(fd, buff);
		std::cout << "CLient username = " << _clients[fd].getClientUserName() << std::endl; 
		std::cout << "BUFF = \"" << buff << "\"" << std::endl;
		if (_clients[fd].getNumberInfo() == 2)
			_clients[fd].setRegistrated(true);
	}

}

void Server::InitServ(char *port, std::string password){
	this->_port = atoi(port);
	this->_password = password;
	SocketCreator();
	std::cout << "Server <" << _fdSocket << "> Connected" << std::endl;
	std::cout << "Waiting to accept a connection...\n";
	while(Server::_signal == false)
	{
		if((poll(&_fds[0],_fds.size(), -1) == -1) && Server::_signal == false)
			throw(std::runtime_error("poll() faild"));
		for(size_t i  = 0; i < _fds.size() ; i++){
			if(_fds[i].revents & POLLIN){
				if(_fds[i].fd == _fdSocket)
					NewClientAccept();
				else
					ReceiveData(_fds[i].fd);
			}
		}
	}
	CloseFds();
	
};
