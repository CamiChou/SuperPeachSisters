#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include "Actor.h"
#include "GameConstants.h"




// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  bool isBlocking(int xCoord, int yCoord);
  bool doesIntersectPeach(int xCoord, int YCoord);
    
  void setJump();
  void setStar(int numTicks);
  void setFire();
    
  void setPeachHP(int num);
    
    
    

private:
    Peach* myPeach;
    std::vector<Actor*> actorVect;
    
};









#endif // STUDENTWORLD_H_
