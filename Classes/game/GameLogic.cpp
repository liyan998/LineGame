#include "GameLogic.h"


bool CGameLogic::init()
{
    Node::init();
    log("Gamelogic init..."); 

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    m_pBoss = Sprite::create("CloseNormal.png");  
    m_pBoss->setScale(1.5f);
    m_pBoss->setPosition(Vec2(100 + origin.x, 300 + origin.y));
    addChild(m_pBoss);

    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_TEST, this); 
     
    return true;
}


void CGameLogic::actionEvent(int evenid, void* pData)
{

    switch (evenid)
    {
    case EVENT_TEST:
    {
                       int data = *(int*)(pData);
                       log("Event_Test:%d", data);

                      

    }
        break;
    default:
        break;
    }


}

void CGameLogic::run(float time)
{




}