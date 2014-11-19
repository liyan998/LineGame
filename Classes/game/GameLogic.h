#ifndef __GAMELOGIC_H__
#define __GAMELOGIC_H__

#include "System.h"
#include "GameElement.h"
#include "Game1Player.h"
#include "MySprite.h"
#include "Path.h"

class CGameLogic : public Node
{

public:

    CREATE_FUNC(CGameLogic)

public:

    virtual bool init();

    //-------------------------------------------

    void run(float time);







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