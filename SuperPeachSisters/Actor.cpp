#include "Actor.h"
#include "StudentWorld.h"



Actor::Actor(int ID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sw):
GraphObject (ID, startX, startY, startDirection, depth, size)
{
    m_alive=true;
    myWorld = sw;
    
    
}





Actor:: ~Actor() {}


bool Actor:: isAlive()
{
    return m_alive;
}






void Actor:: setDead()
{
    m_alive=false;
}



StudentWorld* Actor::getWorld()
{
    return myWorld;
}




bool Actor:: isBlocking()
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
    hasFire=false;
    
}



void Peach:: Bonk()     //IMPLEMENT
{
    if (isInvincible())
        return;
    else
    {
        
        
        
        
        
    }
    
}





void Peach:: doSomething()
{
    if (!isAlive())
        return;
    
    int ch;
    if (getWorld()->getKey(ch))
    {
        switch (ch)
        {
        case KEY_PRESS_LEFT:
            {
                setDirection(180);
                
                
                if (!getWorld()->overlap(getX()-4, getY()))
                    moveTo(getX()-4, getY());
                break;
                
                
                
            }
        case KEY_PRESS_RIGHT:
            {
                setDirection(0);
                
                if (!getWorld()->overlap(getX()+4, getY()))
                    moveTo(getX()+4, getY());
                break;
            }
                
                
                
            
        case KEY_PRESS_UP:
            {
                if (!getWorld()->overlap(getX(), getY()+4))
                    moveTo(getX(), getY()+4);
                break;
                
            }
                
                
        case KEY_PRESS_DOWN:
            {
                if (!getWorld()->overlap(getX(), getY()-4))
                    moveTo(getX(), getY()-4);
                break;
                
            }
                
                
            
                
        }
    
    }
    
    
    
    
}




Peach::~Peach()
{
    
}












//BLOCK

Block::Block(int imageID, int startX, int startY, StudentWorld* sw):

Pipe(imageID,  startX,  startY, sw )

{
    
}



void Block:: Bonk()     //IMPLEMENT
{
    
}






Block::~Block()
{
    
}




void Block::doSomething()
{
    
}



//PIPE


Pipe::Pipe(int imageID, int startX, int startY, StudentWorld* sw):
Actor(imageID,  startX,  startY,  0,  2,  1, sw)
{
    
}


void Pipe:: Bonk()     //IMPLEMENT
{
    
}




void Pipe:: doSomething()
{
    
}


Pipe::~Pipe()
{
    
}



bool Pipe:: isBlocking()
{
    return true;
}









//END BLOCK






//FLAG
Flag::Flag(int imageID, int startX, int startY, StudentWorld* sw):
Actor(imageID,  startX,  startY,  0,  1,  1, sw)
{
    
}



void Flag:: Bonk()     //IMPLEMENT
{
    
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


void Mario:: Bonk()     //IMPLEMENT
{
    
}




//END MARIO











//ENEMIES
