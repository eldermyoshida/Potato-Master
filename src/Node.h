//
//  Node.h
//  Potato-Master
//
//  Created by Elder Yoshida on 4/23/15.
//  Copyright (c) 2015 Elder Yoshida. All rights reserved.
//

#ifndef __Potato_Master__Node__
#define __Potato_Master__Node__

#include <stdio.h>
#include <string>


class Node {

public:
	Node(std::string ip, std::string port);
	std::string ip;
	std::string port;
};


#endif /* defined(__Potato_Master__Node__) */
