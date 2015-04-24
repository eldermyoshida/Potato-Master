//
//  Server.cpp
//  Potato-Master
//
//  Created by Elder Yoshida on 4/23/15.
//  Copyright (c) 2015 Elder Yoshida. All rights reserved.
//

#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_

#include "Connection.h"
#include "Link.h"
#include "CompareLink.h"
#include <unordered_map>
#include <queue>
#include <set>
#include <vector>

class Server {
private:
	int mPort;
	int mListenFD;
	std::unordered_map<std::string,std::priority_queue<Link, std::vector<Link>, CompareLink>> link_map;
	std::set<Node> nodes;
	void processConnection(ConnectionData* data);
	void nodeConnect(std::string request);
	void nodeUpdate(std::string request);

public:
	Server(int port);
	virtual ~Server();
	void nodeJoin(std::string request);

	void Listen();
};

#endif /* SRC_SERVER_H_ */
