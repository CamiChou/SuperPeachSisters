#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include "Block.h"
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    
    Level lev(assetPath());
    string level_file = "level01.txt";
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
                            Block* newBlock = new Block(IID_BLOCK, a*SPRITE_WIDTH, b*SPRITE_HEIGHT, 0, 2, 1, this);

                            actorVect.push_back(newBlock);
                            break;
                            
                        }
                    case Level::peach:
                        {
                            Peach* p = new Peach(IID_PEACH, a*SPRITE_WIDTH, b*SPRITE_HEIGHT,  0, 0, 1.0, this);
                            myPeach=p;
        
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

