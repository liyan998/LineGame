#ifndef __GAMEELEMENT_H__
#define __GAMEELEMENT_H__

#include "System.h"  

/////////////////////////////////////////////////////

class CGameElement : public Node
{

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