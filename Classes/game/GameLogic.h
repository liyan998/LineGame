#ifndef __GAMELOGIC_H__
#define __GAMELOGIC_H__

#include "System.h"
#include "GameElement.h"
#include "Game1Player.h"
#include "MySprite.h"
#include "Path.h"  
#include "Runnable.h"

#include "EventSystem.h"

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

private:

    CBoss*                          m_pBoss;

    std::vector< CGameElement* >    m_oAllElement;

    std::vector< CActor* >          m_oAllActor;

    std::vector< CRander* >         m_oAllRander;

public:

    CPath*                          m_refPath;
    CMySprite*                      m_refSp;
    CGamePlayer*                    m_refPlayer;
    CShowArea*                      m_refShowArea;
};
#endif