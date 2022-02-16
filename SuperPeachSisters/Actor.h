#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;


class Actor: public GraphObject
{
public:
    Actor(int ID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sw);
    virtual ~Actor();
    
    
    virtual void doSomething()=0;
    bool isDamagable();
    bool isAlive();
    int returnHitPoints();
    bool isBlocking();
    bool isBonkable();
    StudentWorld* getWorld(); 
    
    
private:
    bool m_alive;
    int m_hitPoints;
    int m_hp;
    StudentWorld* myWorld;
    
    
    
    
};



class Peach: public Actor
{
public:
    Peach(int ID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sw);
    ~Peach();
    void doSomething();
    void setInvincible();
    bool isInvincible();
    void bonk();
    
private:
    bool m_invincible;
    std::string m_power;
    bool rechargeStatus;
};













// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
