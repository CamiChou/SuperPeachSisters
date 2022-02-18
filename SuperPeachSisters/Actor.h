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
    Peach(int startX, int startY, StudentWorld* sw);
    ~Peach();
    void doSomething();
    void setInvincible();
    bool isInvincible();
    void bonk();
    
private:
    bool rechargeStatus;
    bool tempInvinc;
    bool hasJump;
    bool hasStar;
    bool hasFire;
    
    
};










class Pipe:public Actor
{
public:
    Pipe(int imageID, int startX, int startY, StudentWorld* sw);
    ~Pipe();
    void doSomething();
    
    
    
private:
  
    
    
    
    
};



class Block:public Pipe
{
public:
    Block( int imageID, int startX, int startY, StudentWorld* sw);
    ~Block();
    void doSomething();
    
    
    
    
private:
    
    
    
    
    
};






class Flag:public Actor
{
public:
    Flag(int imageID, int startX, int startY, StudentWorld* sw);
    ~Flag();
    void doSomething();
    
    
private:
    
};



class Mario: public Flag
{
public:
    Mario(int imageID, int startX, int startY, StudentWorld* sw);
    ~Mario();
    void doSomething();
    
private:
    
    
    
    
};















// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
