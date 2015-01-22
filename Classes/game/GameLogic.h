#ifndef __GAMELOGIC_H__
#define __GAMELOGIC_H__

#include "ui/UIWidget.h"

#include "System.h"
#include "GameElement.h"
#include "Game1Player.h"
#include "MySprite.h"
#include "Path.h"  
#include "Runnable.h"
#include "Rander.h"

#include "GameState.h"
#include "EventSystem.h"


#define TIMEOUT                 160             //计时周期

#define CHARSEQUEN_HEALTH       "player:%00d"
#define CHARSEQUEN_TIME         "Time:%ds"
#define CHARSEQUEN_AREA         "AREA:%3.0f%%"

class CGameLogic :
    public Node,
    public CRander,
    public CGameState,
    public CRunnable,
    public CEventHandler
    //public extension::TableViewDataSource, public extension::TableViewDelegate
{

public:

    CREATE_FUNC(CGameLogic)

public:

    CGameLogic() : 
        m_iTimer(0), 
        m_fCounter(0.0f)
        //m_iDropCount(0)
    {}

    virtual bool init();

    virtual void onEnter();

    virtual void onExit() override;

    virtual void run(float time);

    virtual void setState(int state);

    virtual void released();

    virtual void actionEvent(int evenid, EventParm pData);

    virtual void print(DrawNode* dn);

    //------------------------------------------- 

    void h_ActionClose(EventParm pData);

    void h_ActionHit(EventParm pDate);

    void h_ActionAddHealth(EventParm pData);

    void h_ActionBossSkill(EventParm pData);

    void h_ActionBossSkillEnd(EventParm pData);

    void h_ActionBossSkillTornadChange(EventParm pData);

    //圈中后对游戏对象的处理-------------------------------------------------------

    void clearGameElement();

    void clearNpc(CNpc* pNpc, int mode);

    void clearGameObject(CGameArticle* pGameArticle, int mode);         //道具清理

    void clearTornado(CTornado* pTornado, int mode);                    //龙卷风清理

    //-----------------------------------------------------------
    
    void flushArea(float area);

    void flushTime(int time);

    void flushHealth(int health);


    void uiLoadcomplete();

    void releasSkill(cocos2d::Ref* sender, ui::Widget::TouchEventType type);

    //list
    //virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);
    //virtual void scrollViewDidStop(cocos2d::extension::ScrollView* view);
    //virtual void scrollViewDidBegin(cocos2d::extension::ScrollView* view, cocos2d::Point& point);
    //virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);
    //virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    //virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    //virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    //virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);

    //----------------------------------------

    inline void createGameElement();                        //根据出战配置创建Enemey

    void removeGameElement(CGameElement* pElement);

    void getRandVec2(CEnemy* pEnemy);                       //得到随机坐标

    void dropObject();                                      //掉落

    //--------------------------------

    CNpc* findSkillTarget();

    void h_actionSkillConfuse(EventParm pData);

    void checkSkillConfuse();

    void skillConfuseCollWithBoss(CNpc* pNpc, CBoss* boss);

    void skillConfuseCollWithNpc(CNpc* pNpc, CNpc* boss);

    void getLiveNpc(std::vector<CNpc*>& rallNpc, int state);


public:

    CPath*                          m_refPath;
    CMySprite*                      m_refSp;
    CGamePlayer*                    m_refPlayer;
    CShowArea*                      m_refShowArea;

private:

    CBoss*                          m_pBoss;

    std::vector< CGameElement* >    m_oAllElement;

    std::vector< CActor* >          m_oAllActor;

    std::vector< CRander* >         m_oAllRander;

    //-----------------------------------------------------

    int                             m_iTimer;
    float                           m_fCounter;

    Vec2                            m_oBong;//  

    //--------------------------------------------------

    //int                             m_iDropCount;//掉落个数

    std::vector<Vec2>               m_oAllDrop;

    CNpc*                           m_pSkillTarget;

};
#endif
