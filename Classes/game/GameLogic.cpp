#include "GameLogic.h"

#include "ShowArea.h"

bool CGameLogic::init()
{
    Node::init();
    log("Gamelogic init..."); 

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    m_pBoss = CBoss::create();
    m_pBoss->setPosition(Vec2(100 + origin.x, 300 + origin.y));

    addChild(m_pBoss);

    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_CLOSE, this);     
    return true;
}   

void CGameLogic::onExit()
{
    Node::onExit();
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_CLOSE, this);
}


void CGameLogic::actionEvent(int evenid, EventParm pData)
{

    switch (evenid)
    {
    case EVENT_CLOSE:
        h_ActionClose(pData);
        break; 
    default:
        break;
    }
}

void CGameLogic::h_ActionClose(EventParm pData)
{
    m_refShowArea->setClose(m_pBoss->getPosition());
    m_refSp->clearGuide();
    float area = m_refShowArea->getArea();
    log(" Area :%f", area);     

    if (area > WINPART)
    {         
        CEventDispatcher::getInstrance()->dispatchEvent(EVENT_WIN, 0);
    }                  
}

void CGameLogic::run(float time)
{




}


void CGameLogic::setState(int state)
{

}

void CGameLogic::released()
{

    this->removeAllChildren();
}