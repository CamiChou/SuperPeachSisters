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



void Actor::damage(){}












Peach::Peach(int startX, int startY, StudentWorld* sw):
Actor(IID_PEACH, startX, startY, 0, 0, 1, sw)
{
    tempInvinc=false;
    invincible=false;
    hasJump=false;
    hasStar=false;
    hasFlower=false;
    remaining_jump_distance=0;
    
    
}




void Peach::decreaseHP()
{
    m_hitPoints--;
}






void Peach:: Bonk()     //IMPLEMENT
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
    
    
    if (invincible==true)
        starPowerTicks--;
    if (starPowerTicks==0)
        tempInvinc=false;
    
    
    if (tempInvinc==false)
        tempInvincibleTicks--;
    if (tempInvincibleTicks==0)
        tempInvinc=false;
    
    
    if (time_to_recharge_before_next_fire>0)
        time_to_recharge_before_next_fire--;
    
    
    
    
    getWorld()->bonkAllBonkables(getX(), getY());
    
    
    
    
    
    
    
    //JUMP
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
    
    //FALL
    
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
            
        case KEY_PRESS_SPACE:
            {
                if (hasFlower && time_to_recharge_before_next_fire==0)
                {
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    time_to_recharge_before_next_fire=8;
                    
                    
                    if (getDirection()==0)
                    {
                        peachFireball* newPeachFireball = new peachFireball(IID_PEACH_FIRE, getX()+4, getY(), getWorld(), 0);
                        getWorld()->addObject(newPeachFireball);

                    }
                        
                    else if (getDirection()==180)
                    {
                        peachFireball* newPeachFireball = new peachFireball(IID_PEACH_FIRE, getX()-4,getY(), getWorld(), 180);
                        getWorld()->addObject(newPeachFireball);
                    }
                
                       




                }

                break;
            }
                
                
                
            
                
        }
    
    }
    
    
    
    
}


void Peach:: setHP(int num)
{
    m_hitPoints=num;
}


void Peach:: damage()
{
    Bonk();
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



void Block:: Bonk()     //IMPLEMENT
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
            Flower* f = new Flower(IID_FLOWER, getX(), getY()+8, getWorld());
            getWorld()->addObject(f);
            hasFlower=false;
        }
        if (hasMushroom)
        {
            Mushroom* m = new Mushroom(IID_MUSHROOM, getX(),getY()+8, getWorld());
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


void Pipe:: Bonk()     //IMPLEMENT
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



void Flag:: Bonk()     //IMPLEMENT
{
    
}







void Flag:: doSomething()
{
    if (!isAlive())
        return;
    else if (getWorld()->doesIntersectPeach(getX(), getY()))
    {
        getWorld()->increaseScore(1000);
        setDead();
        getWorld()->levelUp();
    }
        
    
    
}


Flag::~Flag(){}


//END FLAG




//Mario
Mario::Mario(int imageID, int startX, int startY, StudentWorld* sw):
Flag(imageID,  startX,  startY, sw)
{}



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





Enemies::Enemies(int imageID, int startX, int startY, StudentWorld* sw)
: Actor(imageID, startX, startY, 180* (rand()%2), 1, 1, sw)
{
    
}


Enemies::~Enemies()
{
    
}


void Enemies::Bonk()
{
    
    
}




void Enemies:: damage()
{
    getWorld()->increaseScore(100);
    setDead();
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


bool Enemies:: isDamagable()
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

Koopa::~Koopa(){}



Piranha::Piranha(int imageID, int startX, int startY, StudentWorld* sw)
:Enemies(imageID, startX, startY, sw)
{
    firingDelay=0;
}


Piranha::~Piranha(){};


void Piranha::doSomething()
{
    if (!isAlive())
        return;
    increaseAnimationNumber();
    if (getWorld()->doesIntersectPeach(getX(), getY()))
    {
        getWorld()->bonkAllBonkables(getX(), getY());
        return;
    }
    
    
    int peachX;
    int peachY;
    getWorld()->whereIsPeach(peachX, peachY);
    if (getY()-peachY>1.5*SPRITE_HEIGHT|| getY()-peachY<-1.5*SPRITE_HEIGHT)
        return;
    
    if (peachX>getX())
        setDirection(0);
    else
        setDirection(180);
        
    if (firingDelay>0)
    {
        firingDelay--;
        return;
    }
    else
    {
        if (((getX()-peachX<8*SPRITE_HEIGHT) && (getX()-peachX>0))|| ((getX()-peachX>-8*SPRITE_HEIGHT)&& (getX()-peachX<0)))
        {
            PiranhaFireball* newPiranhaFireball = new PiranhaFireball(IID_PIRANHA_FIRE, getX(), getY(), getWorld(), getDirection());
            getWorld()->addObject(newPiranhaFireball);
            firingDelay=40;
            
        }

    }
    
    
        
    
}





Projectiles::Projectiles(int imageID, int startX, int startY, int dir, StudentWorld* sw)
: Actor(imageID, startX, startY, dir, 1, 1, sw){}




Projectiles::~Projectiles(){}

void Projectiles::doSomething()
{
    if (!getWorld()->isBlocking(getX(), getY()-2))
        moveTo(getX(), getY()-2);
    

    
    
    
    if (getDirection()==0)
    {
        if (!getWorld()->isBlocking(getX()+2, getY()))
            moveTo(getX()+2, getY());
        else
            hitBlockable();
    }
    else if (getDirection()==180)
    {
        if (!getWorld()->isBlocking(getX()-2, getY()))
            moveTo(getX()-2, getY());
        else
            hitBlockable();
    }
}


void Projectiles::Bonk(){}


void Projectiles::hitBlockable()
{
    setDead();
    changeDirection();
}




//GOODIES

Goodies::Goodies(int imageID, int startX, int startY, StudentWorld* sw)
:Projectiles(imageID, startX, startY, 0, sw){}

Goodies::~Goodies(){}

void Goodies::doSomething()
{
    if (getWorld()->doesIntersectPeach(getX(), getY()))
    {
        setDead();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
Projectiles:Projectiles::doSomething();
    
}


void Goodies::hitBlockable()
{
    changeDirection();
    
}




void Goodies::Bonk()
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





PiranhaFireball::PiranhaFireball(int imageID, int startX, int startY, StudentWorld* sw, int dir)
: Projectiles(imageID, startX, startY, dir, sw){}

PiranhaFireball::~PiranhaFireball(){};


void PiranhaFireball::doSomething()
{
    if (getWorld()->doesIntersectPeach(getX(), getY()))
    {
        getWorld()->damagePeach(getX(), getY());
        setDead();
        return;
    }
    
Projectiles:Projectiles::doSomething();
    
    
    
}






peachHelper::peachHelper (int imageID, int startX, int startY, StudentWorld* sw, int dir)
: Projectiles(imageID, startX, startY, dir, sw){}




peachHelper::~peachHelper(){}


void peachHelper::doSomething()
{
    
    
    if (getWorld()->damageEnemies(getX(), getY()))
    {
        setDead();
        return;
    }
    else
        Projectiles:Projectiles::doSomething();
}

    
    

peachFireball::peachFireball(int imageID, int startX, int startY, StudentWorld* sw, int dir):
peachHelper ( imageID,  startX,  startY,  sw,  dir)
{
}



peachFireball::~peachFireball(){};




