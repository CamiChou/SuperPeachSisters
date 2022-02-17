#include "Actor.h"
#include "StudentWorld.h"



Actor::Actor(int ID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sw): GraphObject (ID, startX, startY, startDirection, depth, size)
{
    m_alive=true;
    myWorld = sw;
    
}





Actor:: ~Actor() {}


bool Actor:: isAlive()
{
    return m_alive;
}





StudentWorld* Actor::getWorld()
{
    return myWorld;
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
        }
    
    }
    
    
    
    
}


Peach::Peach(int ID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sw):
Actor(ID, startX, startY, startDirection, depth, size, sw)
{
    
}



Peach::~Peach()
{
    
}














Block::Block(int ID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sw):
Actor( ID,  startX,  startY,  startDirection,  depth,  size, sw)
{
    
}





Block::~Block()
{
    
}




void Block::doSomething()
{
    
}
