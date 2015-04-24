//
//  CompareLink.h
//  Potato-Master
//
//  Created by Elder Yoshida on 4/24/15.
//  Copyright (c) 2015 Elder Yoshida. All rights reserved.
//

#ifndef __Potato_Master__CompareLink__
#define __Potato_Master__CompareLink__

#include <stdio.h>
#include "Link.h"

using namespace std;
class CompareLink {
public:
	bool operator()(Link& l1, Link& l2);
};


#endif /* defined(__Potato_Master__CompareLink__) */
