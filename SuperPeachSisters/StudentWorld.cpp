#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;


int curr_level=3;


GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}


StudentWorld::~StudentWorld()
{
    cleanUp();
}


int StudentWorld::init()
{
    
    Level lev(assetPath());
    
    string level_file;
    if (curr_level==1)
        level_file = "level01.txt";
    else if (curr_level==2)
        level_file = "level02.txt";
    else if (curr_level==3)
        level_file = "level03.txt";
    
    
    Level::LoadResult result = lev.loadLevel(level_file);
    
    
    
    
    
    if (result == Level::load_fail_file_not_found)
        cerr << "Could not find level01.txt data file" << endl;
    else if (result == Level::load_fail_bad_format)
    {
        cerr << "level01.txt is improperly formatted" << endl;

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
               //             cout << "Location 5,10 is empty" << endl;
                            break;
                        }
                    case Level::block:
                        {
                            Block* newBlock = new Block( IID_BLOCK, a*SPRITE_WIDTH, b*SPRITE_HEIGHT, this);

                            actorVect.push_back(newBlock);
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
    while (it!=actorVect.end())
    {
        (*it)->doSomething();
        it++;
    }
    
    (*myPeach).doSomething();
    


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





bool StudentWorld::overlap(int xCoord, int yCoord)
{
    vector<Actor*>::iterator it;
    it = actorVect.begin();
    
    bool isThereOverlap=false;
    while (it!=actorVect.end())
    {
        
        
        
        if (((*it)->getX() + SPRITE_WIDTH-1) <= xCoord || (*it)->getX()>= xCoord + SPRITE_WIDTH-1 ) //-1?
            it++;
        
        else if (((*it)->getY() + SPRITE_HEIGHT-1) <= yCoord || (*it)->getY()>= yCoord + SPRITE_HEIGHT-1 ) //-1?
            it++;
        else
        {
            isThereOverlap=true;
            it++;
        }


    }
    return isThereOverlap;
    
}

