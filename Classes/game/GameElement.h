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
        CATEGORY_AWARD, //������Ʒ
        CATEGORY_BOSS,  //����
        CATEGORY_NPC    //����
    };

public:

    virtual void run(float time) = 0;

    inline int getCategory(){ return m_iCategory; };

    //virtual void print(DrawNode* dn) =0;

protected:  

    //Sprite*         m_pSp;

    Armature*         m_pSp;

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