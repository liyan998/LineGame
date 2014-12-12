#include "GameLogic.h"

#include "ShowArea.h"

bool CGameLogic::init()
{
    Node::init();
    log("Gamelogic init..."); 

    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_CLOSE, this);     

    
    return true;
}   

void CGameLogic::onEnter()
{
    Node::onEnter();

    log("Gamelogic onEnter..");

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    m_pBoss                 = CBoss::create();
    m_pBoss->m_refShowArea  = m_refShowArea;
    m_pBoss->m_refSp        = m_refSp;

    m_pBoss->setPosition(Vec2(100 + origin.x, 300 + origin.y));
    addChild(m_pBoss);

//     auto boss1 = CBoss::create();     
//     boss1->setPosition(Vec2(300 + origin.x, 300 + origin.y));
//     boss1->m_refShowArea = m_refShowArea;
//     addChild(boss1);
//     m_oAllElement.push_back(boss1);
//     m_oAllRander.push_back(boss1);

    //------------------------------------------------

    m_oAllElement.push_back(m_pBoss);
    //------------------------------------------

    m_oAllRander.push_back(m_pBoss);
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
    switch (m_refShowArea->getPathType())
    {
    case POSITION_AREA_ENDPOINT + POSITION_AREA_ENDPOINT:
    case POSITION_AREA_LINE + POSITION_AREA_LINE:
    case POSITION_AREA_LINE + POSITION_AREA_ENDPOINT:
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
        break;
    default:
        m_refSp->clearGuide();
        return;
        
    }

    
}

void CGameLogic::run(float time)
{

    for (int i = 0; i < m_oAllElement.size();i++)
    {
        m_oAllElement[i]->run(time);
    }


}

void CGameLogic::print(DrawNode* dn)
{

    for (int i = 0; i < m_oAllRander.size();i++)
    {
        m_oAllRander[i]->print(dn);
    }
}


void CGameLogic::setState(int state)
{

}

void CGameLogic::released()
{

    this->removeAllChildren();
}