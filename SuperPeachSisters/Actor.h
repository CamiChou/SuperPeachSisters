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
    bool isAlive();
    void setDead();
    int returnHitPoints();
    StudentWorld* getWorld();
    virtual void Bonk(Actor* bonker)=0;
    virtual bool blockable();
    virtual bool isDamagable();
    virtual bool isEnemy();
    void decreaseHP();
    bool overlap(int xCoord, int yCoord);
    void bonkAllBonkables(int xCoord, int yCoord);

private:
    bool m_alive;
    int m_hitPoints;
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
    bool isDamagable();
    virtual void Bonk(Actor* bonker);
    void jump();
    void setJumpDistance();
    
    
    
    
private:
    bool rechargeStatus;
    bool tempInvinc;
    bool hasJump;
    bool hasStar;
    bool hasFire;
    int remaining_jump_distance;
    bool isJumping;
    
};










class Pipe:public Actor
{
public:
    Pipe(int imageID, int startX, int startY, StudentWorld* sw);
    ~Pipe();
    void doSomething();
    bool blockable();
    void Bonk(Actor* bonker);
    
    
    
private:
      
    
    
};



class Block:public Pipe
{
public:
    Block(int imageID, int startX, int startY, StudentWorld* sw);
    ~Block();
    void doSomething();
    void Bonk(Actor* bonker);
    
private:
    
    
    
    
    
};






class Flag:public Actor
{
public:
    Flag(int imageID, int startX, int startY, StudentWorld* sw);
    ~Flag();
    void doSomething();
    void Bonk(Actor* bonker);
    
private:
    
};



class Mario: public Flag
{
public:
    Mario(int imageID, int startX, int startY, StudentWorld* sw);
    ~Mario();
    void doSomething();
    void Bonk(Actor* bonker);
    
    
    
private:
    
    
    
    
};




class Enemies: public Actor
{
public:
    Enemies(int imageID, int startX, int startY, StudentWorld* sw);
    ~Enemies();
    void doSomething();
    void Bonk(Actor* bonker);
    bool isEnemy();
    void changeDirection();
    
    
private:
    
    
};





class Goomba: public Enemies
{
public:
    Goomba (int imageID, int startX, int startY, StudentWorld* sw);
    ~Goomba();
 
};



class Koopa: public Enemies
{
public:
    Koopa (int imageID, int startX, int startY, StudentWorld* sw);
    ~Koopa();
    
};








// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
