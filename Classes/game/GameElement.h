#ifndef __GAMEELEMENT_H__
#define __GAMEELEMENT_H__

#include "System.h" 
#include "Rander.h"
#include "GameState.h"
#include "ShowArea.h"

/////////////////////////////////////////////////////

class CGameElement : public Node 
{
public:

    enum Category
    {
        CATEGORY_AWARD, //������Ʒ
        CATEGORY_BOSS,  //����
        CATEGORY_NPC    //����
    };

public:

    virtual void run(float time) = 0;

    inline int getCategory(){ return m_iCategory; };

protected:  

    Sprite*         m_pSp;

    int             m_iCategory;    //����
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