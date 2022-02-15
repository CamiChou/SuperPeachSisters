#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class Actor: public GraphObject
{
public:
    Actor();
    virtual ~Actor();
    
    
    void doSomething()=0;  //Virtual?
    
    bool isAlive();
    int returnHitPoints();
    
    
    
private:
    bool m_alive;
    int m_hitPoints;
    int m_hp;
    int m_dir;
    
    
    
    
    
};







// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
