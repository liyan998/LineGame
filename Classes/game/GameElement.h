#ifndef __GAMEELEMENT_H__
#define __GAMEELEMENT_H__

#include "System.h" 
#include "Rander.h"
#include "GameState.h"
#include "ShowArea.h"

#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h"   

/////////////////////////////////////////////////////

using namespace cocostudio;

class CGameElement : public Node, public CRander
{
public:

    enum Category
    {
        CATEGORY_AWARD, //奖励物品
        CATEGORY_BOSS,  //首领
        CATEGORY_NPC    //护卫
    };

public:

    virtual void run(float time) = 0;

    inline int getCategory(){ return m_iCategory; };

    //virtual void print(DrawNode* dn) =0;

protected:  

    //Sprite*         m_pSp;

    Armature*         m_pSp;

    int             m_iCategory;    //类型
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