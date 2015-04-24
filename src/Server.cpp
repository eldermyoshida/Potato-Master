//
//  Server.cpp
//  Potato-Master
//
//  Created by Elder Yoshida on 4/23/15.
//  Copyright (c) 2015 Elder Yoshida. All rights reserved.
//

#include "Server.h"
#include "Socket.h"
#include <thread>
#include "string.h"
#include "Address.h"
#include "Common.h"
#include "unistd.h"
#include <iostream>
#include "Connection.h"
#include "Constants.h"
#include "Node.h"
#include "Link.h"
#include <vector>

using namespace std;


void Server::nodeJoin(std::string request){
	std::string response;
	response.clear();
	
	vector<string> tokenList = Util::split(request, '|');
	if(tokenList.size()<3){
		cerr<<"Join with insufficient parameters!\n";
	}
	
	Node node =  Node::Node(tokenList[1], tokenList[2]);
	int loops = (int)tokenList.size()/3;
	if(loops<=0){
		nodes.push_back(node);
		return;
	}
	
	for(int i=1; i<loops; i++){
		Node server = Node::Node(tokenList[i*3], tokenList[i*3+1]);
		int latency = std::stoi( tokenList[i*3+2]);
		Link link = Link::Link(node, server, latency, true);
		if(link_map.count(link.getLinkID())<=0){
			std::priority_queue<Link, std::vector<Link>, LinkComparator> links;
			links.push(link);
			link_map[link.getLinkID()] = links;
			nodes.push_back(node);
		} else {
			link_map[link.getLinkID()].push(link);
		}
	}
	

	response.append(std::to_string(Constants::PMessages::OK));
	sock->send(response);
	
}

void Server::nodeConnect(std::string request){
	std::string response;
	response.clear();
	
	vector<string> tokenList = Util::split(request, '|');
	if(tokenList.size()!=5){
		cerr<<"Connect wrong number of parameters!\n";
	}
	
	Node node =  Node::Node(tokenList[1], tokenList[2]);


	Node server = Node::Node(tokenList[3], tokenList[4]);

	Link link = Link::Link(node, server, 0, true);
		if(link_map.count(link.getLinkID())<=0){
			
			response.append(std::to_string(Constants::PMessages::NOT_FOUND));

		} else {
			//Found!
			link = link_map[link.getLinkID()].top();
			response.append(std::to_string(Constants::PMessages::RESPONSE));
			response.append("|");
			response.append(link.getLinkID());
		}

	sock->send(response);
}

void Server::nodeUpdate(std::string request){
	
	std::string response;
	response.clear();
	
	vector<string> tokenList = Util::split(request, '|');
	if(tokenList.size()<3){
		cerr<<"Join with insufficient parameters!\n";
	}
	
	Node node =  Node::Node(tokenList[1], tokenList[2]);
	int loops = (int)tokenList.size()/3;
	if(loops<=0){
		nodes.push_back(node);
		return;
	}
	
	for(int i=1; i<loops; i++){
		Node server = Node::Node(tokenList[i*3], tokenList[i*3+1]);
		int latency = std::stoi( tokenList[i*3+2]);
		Link link = Link::Link(node, server, latency, true);
		if(link_map.count(link.getLinkID())<=0){
			std::priority_queue<Link, std::vector<Link>, LinkComparator> links;
			links.push(link);
			link_map[link.getLinkID()] = links;
			nodes.push_back(node);
		} else {
			link_map[link.getLinkID()].push(link);
		}
	}
	
	
	response.append(std::to_string(Constants::PMessages::OK));
	sock->send(response);
}

void Server::processConnection(ConnectionData* data)
{
	// The socket.
	ConnectionData* pDat = data;
	std::string request;
	if (!pDat)
	{
		// Invalid data.
		cerr << "NULL thread data." << endl;
		return;
	}
	
	Socket *sock = new Socket(data->socket);
	if (!sock->receive(request, -1))
	{
		cerr<<"Could not receive node request\n";
		return;
	}
	
	if(request.empty()){
		cerr<<"Empty request!\n";
		return;
	}
	switch (request.at(0)) {
		case Constants::PMessages::JOIN:
			nodeJoin(request);
			break;
		case Constants::PMessages::CONNECT:
			nodeConnect(request);
			break;
		case Constants::PMessages::UPDATE:
			nodeUpdate(request);
			break;
			
		default:
			cerr <<	"Invalid node request\n!";
			break;
	}
}




Server::Server(int port) {
	mPort = port;
	mListenFD = -1;
}

Server::~Server() {
	// TODO Auto-generated destructor stub
	if (mListenFD != -1) {
		close(mListenFD);
	}
}

void Server::Listen() {
	if (mListenFD != -1) {
		// close
		return;
	}
	
	cout << "Starting on port " << mPort << "." << endl;
	mListenFD = socket(PF_INET, SOCK_STREAM, 0);
	if (mListenFD == -1)
	{
		cerr << "Error creating listen socket: " << strerror(errno) << endl;
		return;
	}
	
	// Try to reuse socket. We don't care if it fails really. Yeah yeah security.
	int optval = 1;
	setsockopt(mListenFD, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	
	sockaddr_in listen_addr;
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_port = htons(mPort);
	listen_addr.sin_addr.s_addr = INADDR_ANY;
	
	if (::bind(mListenFD, reinterpret_cast<sockaddr*>(&listen_addr), sizeof(listen_addr)) == -1)
	{
		cerr << "Error binding listen socket: " << strerror(errno) << endl;
		return;
	}
	
	if (listen(mListenFD, 1024) == -1)
	{
		cerr << "Error listening on listen socket: " << strerror(errno) << endl;
		return;
	}
	
	while (true)
	{
		sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(client_addr);
		int newSock = accept(mListenFD, reinterpret_cast<sockaddr*>(&client_addr), &client_addr_len);
		if (newSock == -1)
		{
			cerr << "Error accepting connection: " << strerror(errno) << endl;
			
			// Check if ctrl-c was pressed.
			if (errno == EINTR)
				break;
			usleep(100000); // Just in case.
			continue;
		}
		
		//		cerr << "Accepted connection." << endl;
		ConnectionData* pDat = new ConnectionData;
		pDat->socket = newSock;
		pDat->client = client_addr;
		
		// Create a new thread for the socket!
		thread newConnection;
		newConnection = thread([=] {
			this->processConnection(pDat);
		});		newConnection.detach();
	}
	
	close(mListenFD);
}
