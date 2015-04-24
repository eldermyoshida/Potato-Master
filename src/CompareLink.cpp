//
//  CompareLink.cpp
//  Potato-Master
//
//  Created by Elder Yoshida on 4/24/15.
//  Copyright (c) 2015 Elder Yoshida. All rights reserved.
//

#include "CompareLink.h"
class CompareLink {
public:
	bool operator()(Link& l1, Link& l2)
	{
		return l1.linkLatency<l2.linkLatency;
	}
};
