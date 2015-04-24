//
//  Link.h
//  Potato-Master
//	This class stores the multiple links within the network.
//
//
//  Created by Elder Yoshida on 4/23/15.
//  Copyright (c) 2015 Elder Yoshida. All rights reserved.
//

#ifndef __Potato_Master__Link__
#define __Potato_Master__Link__

#include <stdio.h>
#include "Socket.h"


class Link {
private:
	struct sockaddr mServer, mNode;
	
public:
	Link(sockaddr server, sockaddr node, int latency);
	virtual ~Link();
	std::string getLinkID();
	int linkLatency;
};

#endif /* defined(__Potato_Master__Link__) */
