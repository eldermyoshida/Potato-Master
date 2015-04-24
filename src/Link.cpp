//
//  Link.cpp
//  Potato-Master
//
//  Created by Elder Yoshida on 4/23/15.
//  Copyright (c) 2015 Elder Yoshida. All rights reserved.
//

#include "Link.h"

using namespace std;

Link::Link(sockaddr server, sockaddr node, int latency)
: mServer(server), mNode(node), linkLatency(latency) {}

Link::~Link(){
	
}

bool operator<(const Link& x, const Link& y) {
	return x.linkLatency<y.linkLatency;
}
