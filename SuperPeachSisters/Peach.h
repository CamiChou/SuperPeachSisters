
#ifndef Peach_hpp
#define Peach_hpp


#include "GraphObject.h"
#include "Actor.h"


class Peach: public Actor
{
public:
    void doSomething();
    void setInvincible();
    bool isInvincible();
    void bonk();
    
private:
    bool m_invincible;
    string m_power;
    bool rechargeStatus;
};









#endif /* Peach_hpp */
