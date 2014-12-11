#ifndef __GAMEELEMENT_H__
#define __GAMEELEMENT_H__

#include "System.h" 
#include "Rander.h"
#include "ShowArea.h"

/////////////////////////////////////////////////////

class CGameElement : public Node
{
public:

    virtual void run(float time) = 0;

protected:  

    Sprite* m_pSp;
};

/////////////////////////////////////////////////////


class CActor;
class CStaticObject;//静态物品
class CEnemy;       //
class CBoss;        //首领
class CNpc;         //护卫     

#include "Actor.h"
#include "Enemy.h"
#include "Boss.h"
#include "Npc.h" 


//////////////////////////////////////////////////////

#endif//__GAMEELEMENT_H__