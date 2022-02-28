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
    StudentWorld* getWorld();
    virtual void Bonk()=0;
    virtual bool blockable();
    virtual bool isDamagable();
    virtual bool isEnemy();
    bool overlap(int xCoord, int yCoord);
    void changeDirection();
    virtual void damage();


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
    bool isDamagable();
    void Bonk();
    void activateMushroom();
    void activateStar();
    void activateFlower();
    void setHP(int num);
    void decreaseHP();
    void damage();
    bool peachHasStar();
    bool peachHasMushroom();
    bool peachHasFlower();

    
private:
    bool tempInvinc;    
    bool hasJump;
    bool hasStar;
    bool hasFlower;
    int remaining_jump_distance;
    bool isJumping;
    int m_hitPoints;
    int starPowerTicks;
    int tempInvincibleTicks;
    int time_to_recharge_before_next_fire;
};










class Pipe:public Actor
{
public:
    Pipe(int imageID, int startX, int startY, StudentWorld* sw);
    virtual ~Pipe();
    void doSomething();
    bool blockable();
    virtual void Bonk();
    
};



class Block:public Pipe
{
public:
    Block(int imageID, int startX, int startY, StudentWorld* sw, bool star, bool mush, bool flower);
    ~Block();
    void Bonk();
    
private:
    bool hasStar;
    bool hasMushroom;
    bool hasFlower;
    
};






class Flag:public Actor
{
public:
    Flag(int imageID, int startX, int startY, StudentWorld* sw);
    virtual ~Flag();
    void doSomething();
    void Bonk();
    virtual void toDoNext();

};



class Mario: public Flag
{
public:
    Mario(int imageID, int startX, int startY, StudentWorld* sw);
    ~Mario();
    void toDoNext();
};




class Enemies: public Actor
{
public:
    Enemies(int imageID, int startX, int startY, StudentWorld* sw);
    virtual ~Enemies();
    virtual void doSomething();
    virtual void Bonk();
    bool isEnemy();
    bool isDamagable();
    virtual void damage();
    
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
    void Bonk();
    void damage();
    
};


class Piranha: public Enemies
{
public:
    Piranha(int imageID, int startX, int startY, StudentWorld* sw);
    ~Piranha();
    void doSomething();

private:
    int firingDelay;
    
};






class Projectiles: public Actor
{
public:
    Projectiles(int imageID, int startX, int startY, int dir, StudentWorld* sw);
    virtual ~Projectiles();
    virtual void doSomething();
    void Bonk();
    virtual void hitBlockable();
};






class Goodies: public Projectiles
{
public:
    Goodies(int imageID, int startX, int startY, StudentWorld* sw);
    virtual ~Goodies();
    virtual void doSomething();
    void hitBlockable();
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






class PiranhaFireball:public Projectiles
{
public:
    PiranhaFireball(int imageID, int startX, int startY, StudentWorld* sw, int dir);
    ~PiranhaFireball();
    void doSomething();
};



class peachHelper: public Projectiles
{
public:
    peachHelper(int imageID, int startX, int startY, StudentWorld* sw, int dir);
    virtual ~peachHelper();
    void doSomething();
};


class peachFireball: public peachHelper
{
public:
    peachFireball(int imageID, int startX, int startY, StudentWorld* sw, int dir);
    ~peachFireball();
};


class shell: public peachFireball
{
public:
    shell(int imageID, int startX, int startY, StudentWorld* sw, int dir);
    ~shell();
};


#endif // ACTOR_H_
