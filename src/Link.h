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
#include "Node.h"


class Link {
private:
	struct Node mServer, mNode;
	
public:
	Link(Node node, Node server, int latency, bool valid);
	virtual ~Link();
	std::string getLinkID();
	int linkLatency;
	bool valid = false;
};

#endif /* defined(__Potato_Master__Link__) */
