#ifndef __GAMELOGIC_H__
#define __GAMELOGIC_H__

#include "System.h"
#include "GameElement.h"
#include "Game1Player.h"
#include "MySprite.h"
#include "Path.h"  
#include "Runnable.h"
#include "Rander.h"
#include "GameState.h"
#include "EventSystem.h"

#define TIMEOUT                 160             //��ʱ����

#define CHARSEQUEN_HEALTH       "player:%00d"
#define CHARSEQUEN_TIME         "Time:%ds"
#define CHARSEQUEN_AREA         "AREA:%3.0f%%"

class CGameLogic :
    public Node,
    public CRander,
    public CGameState,
    public CRunnable,
    public CEventHandler
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


    void clearGameElement();

    void clearNpc(CNpc* pNpc, int mode);

    void clearGameObject(CGameArticle* pGameArticle, int mode);       //��������

    
    void flushArea(float area);

    void flushTime(int time);

    void flushHealth(int health);

    //----------------------------------------

    inline void createGameElement();                        //���ݳ�ս���ô���Enemey

    void removeGameElement(CGameElement* pElement);

    void getRandVec2(CEnemy* pEnemy);                       //�õ��������

    void dropObject();                                      //����

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

    //int                             m_iDropCount;//�������

    std::vector<Vec2>               m_oAllDrop;

};
#endif