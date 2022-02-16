//
//  Block.hpp
//  SuperPeachSisters
//
//  Created by Cami Chou on 2/15/22.
//  Copyright © 2022 UCLA Computer Science Department. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp



#include <stdio.h>
#include "Actor.h"

class Block:public Actor
{
public:
    Block(int ID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sw);
    ~Block();
    void doSomething();
    
    
    
    
private:
    
    
    
    
    
};














#endif /* Block_hpp */
