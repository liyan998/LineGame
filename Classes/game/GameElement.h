#ifndef __GAMEELEMENT_H__
#define __GAMEELEMENT_H__

#include "System.h" 

#include "util/Math.h"
#include "util/Util.h"

#include "Rander.h"
#include "Runnable.h"
#include "GameState.h"

#include "ShowArea.h"
#include "MySprite.h"

#include "AnimaAxis.h"

/////////////////////////////////////////////////////

using namespace liyan998;


class CGameElement : 
    public CAnimationAxis,
    public CRander, 
    public CRunnable, 
    public CGameState
{
public:

    enum Category
    {
        CATEGORY_ELEMENT,

        CATEGORY_PROERTY = 0x100,   //道具
        CATEGORY_BOSS    = 0x200,   //首领
        CATEGORY_NPC     = 0x300,   //护卫


        CATEGORY_CAT     = 0X301,   //史来猫

        CATEGORY_TORNADO = 0x400,   //风魔龙龙卷风

    };

public:

    CGameElement():   
        m_fCount(0.0f),
        m_iCategory(CATEGORY_ELEMENT),
        m_iCollR(20),
        m_iStep(1)
    {};

    //------------------------------------

    virtual void run(float time) = 0;

    virtual void print(DrawNode* dn);

    inline int getCategory(){ return m_iCategory; };

    virtual float getCollwithR();                                           //碰撞半径

    //-------------------------------------------------

    bool collwithBorder(const Vec2& inPoint, Vec2& outPoint);               //border碰撞

    bool collwithArea(const Vec2& inPoint, Vec2& outPoint);

    //-------------------------------------

    bool checkRandPosition(const Vec2& inPoint);                            //检查坐标是否符合游戏逻辑标准

    void randPosition(Vec2& outPoint);

    int getStep();

    CAnimationAxis* findCreateByIndex(int index);

public:

    CShowArea*          m_refShowArea;
   
    int                 m_iCollR;       //碰撞半径
    int                 m_iStep;        //移动速度

    float               m_fCount;
    int                 m_iCategory;    //类型
};

/////////////////////////////////////////////////////


class CActor;
class CGameArticle; //静态物品
class CTornado;     //龙卷风

class CEnemy;       //
class CBoss;        //首领
class CNpc;         //护卫    
class CGamePlayer;

class CButterFly;
class CDragon;

class CCat;         //史来喵
//class CMySprite;

#include "Actor.h"

#include "Enemy.h"
#include "Boss.h"

#include "ButterFly.h"
#include "Dragon.h"
#include "Tornado.h"

#include "Npc.h"
#include "Cat.h"

#include "Game1Player.h"

#include "GameArticle.h"

//#include "MySprite.h"

//////////////////////////////////////////////////////

#endif//__GAMEELEMENT_H__