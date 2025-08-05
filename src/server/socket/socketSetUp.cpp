/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socketSetUp.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:20:51 by tripham           #+#    #+#             */
/*   Updated: 2025/08/05 18:18:06 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::setupSocket() {
	this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_serverSocket < 0) {
		perror("socket");
		throw std::runtime_error("Failed to create socket");	
	}
	
	// Allow to reuse the address when restart the server
	int otp = 1;
	if (setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR, &otp, sizeof(otp)) < 0) {
		perror("setsockopt");
		throw std::runtime_error("Failed to set socket options");
	}
	
	// IP address and port number
	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET; // IPv4
	serverAddr.sin_addr.s_addr = INADDR_ANY; //0.0.0.0 (accpet all the Ip)
	serverAddr.sin_port = htons(this->_port); // Convert port to network byte order
	
	// Assign socket to the address (IP + Port)
	if (bind(this->_serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
		perror("bind");
		throw std::runtime_error("Failed to bind socket");
	}
	
	// Listen the connection
	if (listen(this->_serverSocket, SOMAXCONN) == -1) {
		perror("listen");
		throw std::runtime_error("Failed to listen the socket");
	}

	//Add socket server to the list of the socket
	pollfd serverPollFD;
	serverPollFD.fd = this->_serverSocket;
	serverPollFD.events = POLLIN;
	serverPollFD.revents = 0;
	this->_pollFDs.push_back(serverPollFD);

	std::cout << "Server is listening on port " << _port << std::endl;
}