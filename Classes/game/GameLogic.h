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
    public CRunnable,
    public CEventHandler
{

public:

    CREATE_FUNC(CGameLogic)

public:

    virtual bool init();

    virtual void run(float time);

    virtual void actionEvent(int evenid, void* pData);

    //-------------------------------------------




private:

    Sprite* m_pBoss;

    std::vector< CGameElement* >    m_oAllElement;

public:

    CPath*                          m_refPath;
    CMySprite*                      m_refSp;
    CGamePlayer*                    m_refPlayer;
    CShowArea*                      m_refShowArea;
};
#endif