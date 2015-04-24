//
//  Link.cpp
//  Potato-Master
//
//  Created by Elder Yoshida on 4/23/15.
//  Copyright (c) 2015 Elder Yoshida. All rights reserved.
//

#include "Link.h"

using namespace std;

Link::Link(struct sockaddr server, struct sockaddr node, int latency)
: mServer(server), mNode(node), linkLatency(latency) {
	mServer.sa_family = AF_INET;
}

Link::~Link(){
	
}

bool operator<(const Link& x, const Link& y) {
	return x.linkLatency<y.linkLatency;
}

std::string Link::getLinkID(){
	
	char s[INET6_ADDRSTRLEN];
	switch(mServer.sa_family) {
		case AF_INET:
			inet_ntop(AF_INET, &(((struct sockaddr_in *)&mServer)->sin_addr),
					  s, INET6_ADDRSTRLEN);
			break;
			
		case AF_INET6:
			inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)&mServer)->sin6_addr),
					  s, INET6_ADDRSTRLEN);
			break;
			
		default:
			strncpy(s, "Unknown AF", INET6_ADDRSTRLEN);
			return "";
	}
	std::string Str = std::string(s);

	return Str;

	
}
