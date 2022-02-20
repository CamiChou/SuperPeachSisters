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
    bool overlap(int xCoord, int yCoord);
    void bonkAllBonkables(int xCoord, int yCoord);
    void changeDirection();


private:
    bool m_alive;
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
    void setJumpDistance();
    
    
    void activateMushroom();
    void activateStar(int numTicks);
    void activateFlower();
    void setHP(int num);
    void decreaseHP();

    
    
    
    
private:
    bool rechargeStatus;
    bool tempInvinc;
    bool hasJump;
    bool hasStar;
    bool hasFlower;
    int remaining_jump_distance;
    bool isJumping;
    int m_hitPoints;
    int starPowerTicks;
    
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
    Block(int imageID, int startX, int startY, StudentWorld* sw, bool star, bool mush, bool flower);
    ~Block();
    void doSomething();
    void Bonk(Actor* bonker);
    
private:
    bool hasStar;
    bool hasMushroom;
    bool hasFlower;
    
    
    
    
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



class Goodies: public Actor
{
public:
    Goodies(int imageID, int startX, int startY, StudentWorld* sw);
    ~Goodies();
    void doSomething();    
    
    
};






class Star: public Goodies
{
public:
    Star(int imageID, int startX, int startY, StudentWorld* sw);
    ~Star();
    void doSomething();
    
};



class Flower: public Goodies
{
public:
    Flower(int imageID, int startX, int startY, StudentWorld* sw);
    ~Flower();
    void doSomething();
    
};




class Mushroom: public Goodies
{
public:
    Mushroom(int imageID, int startX, int startY, StudentWorld* sw);
    ~Mushroom();
    void doSomething();
};






// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
