#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>

#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw


using namespace std;


int curr_level=1;


GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath):GameWorld(assetPath){}

StudentWorld::~StudentWorld(){cleanUp();}

int StudentWorld::init()
{
    leveledUp=false;
    Level lev(assetPath());
    string level_file;
    
    
    
    ostringstream oss;
    oss << "level" << setw(2) << setfill('0') << curr_level << ".txt";
    string st = oss.str();
    level_file=st;
    Level::LoadResult result = lev.loadLevel(level_file);
    
    
    if (result == Level::load_fail_file_not_found)
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_fail_bad_format)
    {
        return GWSTATUS_LEVEL_ERROR;
    }
    
    
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        Level::GridEntry ge;
    
        for (int a=0; a<GRID_WIDTH ; a++)
        {
            for (int b=0; b<GRID_HEIGHT ; b++)
            {
                ge = lev.getContentsOf(a, b);
                switch (ge)
                    {
                    case Level::empty:
                        {
                         cerr << "empty" << endl;
                            break;
                        }
                    case Level::block:
                        {
                            Block* newBlock = new Block( IID_BLOCK, a*SPRITE_WIDTH, b*SPRITE_HEIGHT, this, false, false, false);
                            actorVect.push_back(newBlock);
                            break;
                        }
                        case Level::star_goodie_block:
                        {
                            Block* newStarBlock = new Block( IID_BLOCK, a*SPRITE_WIDTH, b*SPRITE_HEIGHT, this, true, false, false);
                            actorVect.push_back(newStarBlock);
                            break;
                        }
                            
                           
                        case Level::mushroom_goodie_block:
                        {
                            Block* newMushBlock = new Block( IID_BLOCK, a*SPRITE_WIDTH, b*SPRITE_HEIGHT, this, false, true, false);
                            actorVect.push_back(newMushBlock);
                            break;
                        }
                        
                        case Level::flower_goodie_block:
                        {
                            Block* flowerBlock = new Block( IID_BLOCK, a*SPRITE_WIDTH, b*SPRITE_HEIGHT, this, false, false, true);
                            actorVect.push_back(flowerBlock);
                            break;
                        }
                            
                    case Level::peach:
                        {
                            Peach* p = new Peach(a*SPRITE_WIDTH, b*SPRITE_HEIGHT, this);
                            myPeach=p;
                            break;
                        }
                            
                            
                        case Level::pipe:
                        {
                            Pipe* newPipe= new Pipe(IID_PIPE,a*SPRITE_WIDTH, b*SPRITE_HEIGHT, this );
                            actorVect.push_back(newPipe);
                            break;
                        }
                            
                        case Level:: flag:
                        {
                            Flag* newFlag= new Flag(IID_FLAG,a*SPRITE_WIDTH, b*SPRITE_HEIGHT, this );
                            actorVect.push_back(newFlag);
                            break;
                            
                        }
                            
                        case Level:: mario:
                        {
                            Mario* m_Mario= new Mario(IID_MARIO, a*SPRITE_WIDTH, b*SPRITE_HEIGHT, this );
                            actorVect.push_back(m_Mario);
                            break;
                        }
                            
                        case Level:: goomba:
                        {
                            Goomba* newGoomba = new Goomba(IID_GOOMBA, a*SPRITE_WIDTH, b*SPRITE_HEIGHT, this);
                            actorVect.push_back(newGoomba);
                            break;
                        }
                            
                        case Level::koopa:
                        {
                            Koopa* newKoopa = new Koopa(IID_KOOPA, a*SPRITE_WIDTH, b*SPRITE_HEIGHT, this);
                            actorVect.push_back(newKoopa);
                            break;
                        }
                        case Level:: piranha:
                        {
                            Piranha* newPirhanna = new Piranha(IID_PIRANHA, a*SPRITE_WIDTH, b*SPRITE_HEIGHT, this);
                            actorVect.push_back(newPirhanna);
                            break;
                        }
                    }
            }
        }
    
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    vector<Actor*>::iterator it;
    it = actorVect.begin();
    while (it!=actorVect.end() && (*it)->isAlive())
    {
        (*it)->doSomething();
        it++;
    }
    if (myPeach->isAlive())
        (*myPeach).doSomething();

    else if (!myPeach->isAlive())
    {
        playSound(SOUND_PLAYER_DIE);
        return GWSTATUS_PLAYER_DIED;
    }
        
    if (leveledUp==true)
    {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    if (gameOver==true)
    {
        playSound(SOUND_GAME_OVER);
        return GWSTATUS_PLAYER_WON; 
    }
    
    
    removeDead();
    
    displayScore();
    
    return GWSTATUS_CONTINUE_GAME;
}




void StudentWorld::cleanUp()
{
    vector<Actor*>::iterator it;
    it = actorVect.begin();
    while (it!=actorVect.end())
    {
        delete (*it);
        it = actorVect.erase(it);
    }
    delete myPeach;
}




bool StudentWorld::isBlocking(int xCoord, int yCoord)
{
    vector<Actor*>::iterator it;
    it = actorVect.begin();
    bool m = false;
    while (it!=actorVect.end())
    {
        if ((*it)->blockable() && (*it)->overlap(xCoord, yCoord))
        {
            m=true;
            it++;
        }
        else
            it++;
    }
    return m;
}


bool StudentWorld:: doesIntersectPeach(int xCoord, int yCoord)
{
    if (myPeach->overlap(xCoord, yCoord))
        return true;
    return false;
}







void StudentWorld:: setJump()
{
    myPeach->activateMushroom();
}
void StudentWorld:: setStar()
{
    myPeach->activateStar();
}
void StudentWorld:: setFire()
{
    myPeach->activateFlower();
    
}



void StudentWorld:: setPeachHP(int num)
{
    myPeach->setHP(num);
}







void StudentWorld::bonkAllBonkables(int x, int y)
{
    vector<Actor*>::iterator it;
    it = actorVect.begin();
    while (it!=actorVect.end())
    {
        if ((*it)->overlap(x, y)&& (*it)->isAlive())
            (*it)->Bonk();
        it++;
    }
}



void StudentWorld::addObject(Actor* a)
{
    actorVect.push_back(a);
}


void StudentWorld:: removeDead()
{
    vector<Actor*>::iterator it;
    it = actorVect.begin();
    while (it!=actorVect.end())
    {
        if (!(*it)->isAlive())
        {
            delete (*it);
            it = actorVect.erase(it);
        }
        else
        {
            it++;
        }
    }
}


void StudentWorld::levelUp()
{
    if (!gameOver)
        curr_level+=1;
    leveledUp=true;
    playSound(SOUND_FINISHED_LEVEL);
}



void StudentWorld:: GameOver()
{
    gameOver=true;
}




void StudentWorld:: whereIsPeach(int &x, int &y)
{
    x = myPeach->getX();
    y = myPeach->getY();
}




bool StudentWorld:: damageEnemies(int x, int y)
{
    
    vector<Actor*>::iterator it;
    it = actorVect.begin();
    bool didDamage=false;
    while (it!=actorVect.end())
    {

        if ((*it)->isEnemy()&&(*it)->overlap(x, y)&& (*it)->isDamagable()&&(*it)->isAlive())
        {
            (*it)->damage();
            didDamage=true;
        }
        it++;
    }
    return didDamage;
}



void StudentWorld::bonkDamagePeach(int x, int y)
{
    if (doesIntersectPeach(x, y))
        myPeach->Bonk();
}



bool StudentWorld:: doesPeachHaveStar()
{
    if (myPeach->peachHasStar())
        return true;
     
    return false;
    
}

bool StudentWorld::doesPeachHaveFlower()
{
    if (myPeach->peachHasFlower())
        return true;
     
    return false;
    
}
bool StudentWorld::doesPeachHaveMushroom()
{
    if (myPeach->peachHasMushroom())
        return true;
     
    return false;
    
}








void StudentWorld:: displayScore()
{
    ostringstream oss;
    oss << "Lives: " << getLives()  << " ";
    oss << "Level: 0" << getLevel() << " ";
    oss << "Points: " << setw(6) << setfill('0') << getScore() << " ";
    if (myPeach->peachHasStar())
        oss << "StarPower! ";
    if (myPeach->peachHasFlower())
        oss<< "ShootPower! " ;
    if (myPeach->peachHasMushroom())
        oss << "JumpPower! ";
    string s = oss.str();
    setGameStatText(s);
}
