/*
 * ProxyServer.h
 *
 *  Created on: Apr 11, 2015
 *      Author: jonno
 */

#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_

#include "Connection.h"
#include "Link.h"
#include <unordered_map>
#include <queue>

class Server {
private:
	int mPort;
	int mListenFD;
	std::unordered_map<std::string,std::priority_queue<Link>> link_map;
	void processConnection(ConnectionData* data);
	
public:
	Server(int port);
	virtual ~Server();

	void Listen();
};

#endif /* SRC_SERVER_H_ */
