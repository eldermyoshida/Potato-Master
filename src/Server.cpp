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
#include <boost/algorithm/string.hpp>



#include <boost/tokenizer.hpp>

using namespace std;

void Server::nodeJoin(std::string request){

	
	vector<string> tokenList;
	split(tokenList, request, boost::is_any_of("|"), boost::token_compress_on);
	if(tokenList.size()<3){
		cerr<<"Join with insufficient parameters!\n";
	}
	
	Node node =  Node::Node(tokenList[1], tokenList[2]);
	int loops = (int)tokenList.size()/3;
	if(loops<=0){
		nodes.insert(node);
		return;
	}
	
	for(int i=1; i<loops; i++){
		Node server(tokenList[i*3], tokenList[i*3+1]);
		int latency = std::stoi( tokenList[i*3+2]);
		Link link = Link::Link(node, server, latency, true);
		priority_queue<Link> links;
		if(link_map.count(link.getLinkID())>0){
			//has a key, add it!
			link_map[link.getLinkID()].push(link);
		} else {
			//do we need this?
			link_map[link.getLinkID()] = links;
			link_map[link.getLinkID()].push(link);
		}
		
	}
	
	
}

void Server::nodeConnect(std::string request){
	
	
}

void Server::nodeUpdate(std::string request){
	
	
}

void parseString(std::string){
	
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
	
	std::unique_ptr<Socket> sock = std::make_unique<Socket>(data->socket);
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
