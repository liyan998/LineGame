#include "GameLogic.h"


bool CGameLogic::init()
{
    Node::init();
    log("Gamelogic init..."); 


    m_pBoss = Sprite::create("CloseNormal.png");  
    m_pBoss->setScale(1.5f);
    m_pBoss->setPosition(Vec2(100, 500));
    addChild(m_pBoss);

    
    schedule(schedule_selector(CGameLogic::run));
    return true;
}


void CGameLogic::run(float time)
{




}