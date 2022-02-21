#include "Actor.h"
#include "StudentWorld.h"



Actor::Actor(int ID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sw):
GraphObject (ID, startX, startY, startDirection, depth, size)
{
    m_alive=true;
    myWorld = sw;
        
}

Actor:: ~Actor() {}




void Actor::changeDirection()
{
    if (getDirection()==0)
        setDirection(180);
    else if (getDirection()==180)
        setDirection(0);
}



bool Actor:: isAlive()
{
    return m_alive;
}


bool Actor::overlap(int xCoord, int yCoord)
{
    if ((getX() + SPRITE_WIDTH-1) < xCoord || getX()> xCoord + SPRITE_WIDTH-1 )
        return false;
    
    else if ((getY() + SPRITE_HEIGHT-1) < yCoord || (getY()> yCoord + SPRITE_HEIGHT-1 )) //-1?
        return false;
    else
        return true;
}







bool Actor:: isEnemy()
{
    return false;
}



void Actor:: setDead()
{
    m_alive=false;
}



StudentWorld* Actor::getWorld()
{
    return myWorld;
}




bool Actor:: blockable()
{
    return false;
}




bool Actor:: isDamagable()
{
    return false;
}
















Peach::Peach(int startX, int startY, StudentWorld* sw):
Actor(IID_PEACH, startX, startY, 0, 0, 1, sw)
{
    tempInvinc=false;
    hasJump=false;
    hasStar=false;
    hasFlower=false;
    remaining_jump_distance=0;
    
}




void Peach::decreaseHP()
{
    m_hitPoints--;
}






void Peach:: Bonk(Actor* bonker)     //IMPLEMENT
{
    decreaseHP();
    

}


bool Peach:: isDamagable()
{
    return true;
}




void Peach:: activateMushroom()
{
    hasJump=true;
}
void Peach::activateStar(int ticks)
{
    starPowerTicks=150;
    hasStar=true;
}
void Peach::activateFlower()
{
    hasFlower=true;
}









void Peach:: doSomething()
{
    if (!isAlive())
        return;
    
    
    if (isJumping==true && remaining_jump_distance>0)
    {
        if (!getWorld()->isBlocking(getX(), getY()+4))
        {
            moveTo(getX(), getY()+4);
            remaining_jump_distance-=1;
        }
        else
        {
            getWorld()->bonkAllBonkables(getX(), getY()+4);
            remaining_jump_distance=0;
            isJumping=false;
        }
    }
    
    else if (!getWorld()->isBlocking(getX(), getY()-2)||!getWorld()->isBlocking(getX(), getY()-1||!getWorld()->isBlocking(getX(), getY()-3)))
    {
        moveTo(getX(), getY()-4);
    }
                                                                                                
    if (overlap(getX(), getY()))
        getWorld()->bonkAllBonkables(getX(), getY());
    
    
    
    
    
    
    
    
    
    int ch;
    if (getWorld()->getKey(ch))
    {
        switch (ch)
        {
        case KEY_PRESS_LEFT:
            {
                setDirection(180);
                
                
                if (!getWorld()->isBlocking(getX()-4, getY()))
                    moveTo(getX()-4, getY());
                else
                    getWorld()-> bonkAllBonkables(getX()-4, getY());
                break;
            }
        case KEY_PRESS_RIGHT:
            {
                setDirection(0);
                
                if (!getWorld()->isBlocking(getX()+4, getY()))
                    moveTo(getX()+4, getY());
                else
                    getWorld()-> bonkAllBonkables(getX()+4, getY()); 
                break;
            }
                
                
            
        case KEY_PRESS_UP:
            {
                getWorld()->playSound(SOUND_PLAYER_JUMP);
                isJumping=true;
                if (getWorld()->isBlocking(getX(), getY()-1))
                {
                    if (hasJump==true)
                        remaining_jump_distance=12;
                    else
                        remaining_jump_distance=8;
                }
                break;
            }
                
        case KEY_PRESS_DOWN:
            {
                if (!getWorld()->isBlocking(getX(), getY()-4))
                    moveTo(getX(), getY()-4);
                break;
                
            }
                
                
            
                
        }
    
    }
    
    
    
    
}


void Peach:: setHP(int num)
{
    m_hitPoints=num;
}




Peach::~Peach()
{
    
}












//BLOCK

Block::Block(int imageID, int startX, int startY, StudentWorld* sw, bool star, bool mush, bool flower):
Pipe(imageID,  startX,  startY, sw)
{
    hasStar=star;
    hasMushroom=mush;
    hasFlower=flower;
    
}



void Block:: Bonk(Actor* bonker)     //IMPLEMENT
{
    if (hasStar==false && hasFlower==false && hasMushroom==false)
        getWorld()->playSound(SOUND_PLAYER_BONK);
    else
    {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        if (hasStar)
        {
            Star* s = new Star(IID_STAR, getX(), getY()+SPRITE_HEIGHT+8, getWorld());
            getWorld()->addObject(s);
            hasStar=false;
        }
            
        if (hasFlower)
        {
            Flower* f = new Flower(IID_FLOWER, getX(), getY()+ SPRITE_HEIGHT+8, getWorld());
            getWorld()->addObject(f);
            hasFlower=false;
        }
        if (hasMushroom)
        {
            Mushroom* m = new Mushroom(IID_MUSHROOM, getX(),getY()+ SPRITE_HEIGHT+8, getWorld());
            getWorld()->addObject(m);
            hasMushroom=false; 
        }
            
            
    }
    
    
}


Block::~Block()
{
    
}


void Block::doSomething() {}




//PIPE
Pipe::Pipe(int imageID, int startX, int startY, StudentWorld* sw):
Actor(imageID,  startX,  startY,  0,  2,  1, sw)
{
    
}


void Pipe:: Bonk(Actor* bonker)     //IMPLEMENT
{
    
}



void Pipe:: doSomething()
{
    
}


Pipe::~Pipe()
{
    
}



bool Pipe:: blockable()
{
    return true;
}





//END PIPE






//FLAG
Flag::Flag(int imageID, int startX, int startY, StudentWorld* sw):
Actor(imageID,  startX,  startY,  0,  1,  1, sw)
{
    
}



void Flag:: Bonk(Actor* bonker)     //IMPLEMENT
{
    
    
    
    setDead();
    
}







void Flag:: doSomething()
{
    
}


Flag::~Flag()
{
    
}






//END FLAG




//Mario
Mario::Mario(int imageID, int startX, int startY, StudentWorld* sw):
Flag(imageID,  startX,  startY, sw)
{
    
}



void Mario:: doSomething()
{
    
}


Mario::~Mario()
{
    
}


void Mario:: Bonk(Actor* bonker)     //IMPLEMENT
{
    
}




//END MARIO
















//ENEMIES





Enemies::Enemies(int imageID, int startX, int startY, StudentWorld* sw)
: Actor(imageID, startX, startY, 180* (rand()%2), 1, 1, sw)
{
    
}


Enemies::~Enemies()
{
    
}


void Enemies::Bonk(Actor* bonker)
{
    
    
}






void Enemies::doSomething()
{
    if (!isAlive())
        return;
    
    
    
    
    
    
    if (getDirection()==0)
    {
        if (!getWorld()->isBlocking(getX()+1, getY()) && getWorld()->isBlocking(getX()+SPRITE_WIDTH+1, getY()-1))
            moveTo(getX()+1, getY());
        else
        {
            changeDirection();
        }
    }
    else if (getDirection()==180)
    {
        if (!getWorld()->isBlocking(getX()-1, getY()) && getWorld()->isBlocking(getX()-SPRITE_WIDTH-1, getY()-1))
            moveTo(getX()-1, getY());
        else
            changeDirection();
    }
}


bool Enemies::isEnemy()
{
    return true;
}




//GOOMBA


Goomba::Goomba(int imageID, int startX, int startY, StudentWorld* sw):
Enemies(imageID, startX, startY, sw)
{
    
}


Goomba::~Goomba(){}





//KOOPA

Koopa::Koopa(int imageID, int startX, int startY, StudentWorld* sw):
Enemies(imageID, startX, startY, sw)
{
    
}

Koopa::~Koopa()
{
    
}






//GOODIES

Goodies::Goodies(int imageID, int startX, int startY, StudentWorld* sw)
: Actor(imageID, startX, startY, 0, 1, 1, sw){}

Goodies::~Goodies(){}

void Goodies::doSomething()
{
    if (getWorld()->doesIntersectPeach(getX(), getY()))
    {
        setDead();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    else
    {
        if (!getWorld()->isBlocking(getX(), getY()-2))
            moveTo(getX(), getY()-2);
        
        
        if (getDirection()==0)
        {
            if (!getWorld()->isBlocking(getX()+2, getY()))
                moveTo(getX()+2, getY());
            else
            {
                changeDirection();
            }
        }
        else if (getDirection()==180)
        {
            if (!getWorld()->isBlocking(getX()-2, getY()))
                moveTo(getX()-2, getY());
            else
                changeDirection();
        }
    }
    
}



void Goodies::Bonk(Actor* bonker)
{
    
}



//STAR



Star:: Star(int imageID, int startX, int startY, StudentWorld* sw) :Goodies(imageID, startX, startY, sw){}


Star::~Star(){};


void Star::doSomething()
{
    Goodies::doSomething();
    getWorld()->increaseScore(100);
    getWorld()->setStar(150);
}




//FLOWER

Flower::Flower(int imageID, int startX, int startY, StudentWorld* sw)
:Goodies(imageID, startX, startY, sw)
{
    
}

Flower::~Flower(){};


void Flower:: doSomething()
{
    Goodies::doSomething();
    getWorld()->increaseScore(50);
    getWorld()->setFire();
    getWorld()->setPeachHP(2);
}




//MUSHROOM


Mushroom::Mushroom(int imageID, int startX, int startY, StudentWorld* sw)
:Goodies(imageID, startX, startY, sw)
{}


Mushroom::~Mushroom(){};

void Mushroom:: doSomething()
{
    Goodies::doSomething();
    getWorld()->increaseScore(75);
    getWorld()->setJump();
    getWorld()->setPeachHP(2);
}
