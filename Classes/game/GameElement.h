#ifndef __GAMEELEMENT_H__
#define __GAMEELEMENT_H__

#include "System.h" 

// #include "cocostudio/CCArmatureDataManager.h"
// #include "cocostudio/CCArmature.h"   

#include "util/Math.h"
#include "util/Util.h"

#include "Rander.h"
#include "Runnable.h"
#include "GameState.h"

#include "ShowArea.h"
#include "MySprite.h"

#include "AnimaAxis.h"

/////////////////////////////////////////////////////

//using namespace cocostudio;
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
        CATEGORY_AWARD, //��Ʒ
        CATEGORY_BOSS,  //����
        CATEGORY_NPC    //����
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

    //-------------------------------------------------

//     void clearCurrentAnimation();
// 
//     void setCurrentAnimation(const char* arname);

    //-------------------------------------

    bool checkRandPosition(const Vec2& inPoint);                             //��������Ƿ������Ϸ�߼���׼

    void randPosition();

    bool collwithBorder(const Vec2& inPoint, Vec2& outPoint);               //border��ײ

    bool collwithArea(const Vec2& inPoint, Vec2& outPoint);

public:

    CShowArea*          m_refShowArea;
   
    int                 m_iCollR;       //��ײ�뾶
    int                 m_iStep;        //�ƶ��ٶ�

    float               m_fCount;
    int                 m_iCategory;    //����

    //Armature*           m_pSp;

protected:  

    //Sprite*         m_pSp;


    //----------------------------------

};

/////////////////////////////////////////////////////


class CActor;
class CGameArticle;//��̬��Ʒ
class CEnemy;       //
class CBoss;        //����
class CNpc;         //����    
class CGamePlayer;
//class CMySprite;

#include "Actor.h"
#include "Enemy.h"
#include "Boss.h"
#include "Npc.h"
#include "Game1Player.h"
#include "GameArticle.h"
//#include "MySprite.h"

//////////////////////////////////////////////////////

#endif//__GAMEELEMENT_H__