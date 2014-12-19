#ifndef __GAMEELEMENT_H__
#define __GAMEELEMENT_H__

#include "System.h" 

#include "Rander.h"
#include "Runnable.h"
#include "GameState.h"

#include "ShowArea.h"
#include "MySprite.h"

#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h"   

/////////////////////////////////////////////////////

using namespace cocostudio;

class CGameElement : public Layer, public CRander, public CRunnable
{
public:

    enum Category
    {
        CATEGORY_ELEMENT,
        CATEGORY_AWARD, //奖励物品
        CATEGORY_BOSS,  //首领
        CATEGORY_NPC    //护卫
    };

public:

    CGameElement():
        m_pSp(nullptr),
        m_fCount(0.0f),
        m_iCategory(CATEGORY_ELEMENT)
    {};

    //------------------------------------

    virtual void run(float time) = 0;

    inline int getCategory(){ return m_iCategory; };

    //-------------------------------------------------

    void clearCurrentAnimation();

    void setCurrentAnimation(const char* arname);

   
protected:  

    //Sprite*         m_pSp;

    float               m_fCount;

    Armature*           m_pSp;

    int                 m_iCategory;    //类型
};

/////////////////////////////////////////////////////


class CActor;
class CStaticObject;//静态物品
class CEnemy;       //
class CBoss;        //首领
class CNpc;         //护卫    
class CGamePlayer;

#include "Actor.h"
#include "Enemy.h"
#include "Boss.h"
#include "Npc.h"
#include "Game1Player.h"


//////////////////////////////////////////////////////

#endif//__GAMEELEMENT_H__