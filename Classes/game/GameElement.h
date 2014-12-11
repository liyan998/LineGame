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
class CStaticObject;//��̬��Ʒ
class CEnemy;       //
class CBoss;        //����
class CNpc;         //����     

#include "Actor.h"
#include "Enemy.h"
#include "Boss.h"
#include "Npc.h" 


//////////////////////////////////////////////////////

#endif//__GAMEELEMENT_H__