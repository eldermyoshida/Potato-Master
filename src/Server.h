/*
 * ProxyServer.h
 *
 *  Created on: Apr 11, 2015
 *      Author: jonno
 */

#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_

#include "Connection.h"
#include <unordered_map>


class Server {
private:
	int mPort;
	int mListenFD;
	std::unordered_map<std::string,std::string> mymap;
	
public:
	Server(int port);
	virtual ~Server();

	void Listen();
};

#endif /* SRC_SERVER_H_ */
