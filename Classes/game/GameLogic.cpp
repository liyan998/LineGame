#include "GameLogic.h"


bool CGameLogic::init()
{
    Node::init();
    log("Gamelogic init..."); 

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    m_pBoss = Sprite::create("CloseNormal.png");  
    m_pBoss->setScale(1.5f);
    m_pBoss->setPosition(Vec2(100 + origin.x, 500 + origin.y));
    addChild(m_pBoss);

    
    schedule(schedule_selector(CGameLogic::run));
    return true;
}


void CGameLogic::run(float time)
{




}