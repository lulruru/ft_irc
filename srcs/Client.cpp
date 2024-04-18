/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: russelenc <russelenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:24:53 by russelenc          #+#    #+#             */
/*   Updated: 2024/03/23 19:24:53 by russelenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Client.hpp"

/* ************************************************************************** */
/*                     Constructeurs & Destructeurs                   		  */
/* ************************************************************************** */

Client::Client() {
	_registrated = false;
	_pass = false;
	_info = -1;
}


Client::Client(Client const &src) {
	(void)src;
}

Client::~Client() {

}

/* ************************************************************************** */
/*                     Surcharges d'opérateurs                  		      */
/* ************************************************************************** */

Client&	Client::operator=(Client const &rhs) {
	(void)rhs;
	return (*this);
}

/* ************************************************************************** */
/*                    		 Getters & Setters                  		      */
/* ************************************************************************** */

// bool Client::getClientlock(){return this->_lock;}

/* ************************************************************************** */
/*                   			  Méthodes                 		              */
/* ************************************************************************** */
