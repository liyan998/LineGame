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
    createGameElement();    
}

void CGameLogic::onExit()
{
    Node::onExit();
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_CLOSE, this);
}



inline
void CGameLogic::createGameElement()
{
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();

    m_pBoss = CBoss::create();
    m_pBoss->m_refShowArea  = m_refShowArea;
    m_pBoss->m_refSp        = m_refSp;

    m_pBoss->randPosition();

    addChild(m_pBoss);

    m_oAllElement.push_back(m_pBoss);
    m_oAllRander.push_back(m_pBoss); 

    //------------------------------------------------

    const int numNpc = 1;
    for (int i = 0; i < numNpc;i++)
    {
        auto npc = CNpc::create();
        npc->m_refShowArea  = m_refShowArea;
        npc->m_refSp        = m_refSp;

        npc->randPosition();

        addChild(npc);

      m_oAllElement.push_back(npc);
      m_oAllRander.push_back(npc);
    }

    //------------------------------------------

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
                        

        if (!m_refShowArea->isCloseArea())
        {
            return;
        }
        m_refShowArea->clearAreaIndex();



        clearGameElement();
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


void CGameLogic::clearGameElement()
{

    int rmode = m_refShowArea->hasIncludeMaster(m_pBoss->getPosition()) ? MODEL_IN: MODEL_OUT;
    
    for (int i = 0; i < m_oAllElement.size();i++)
    {
        int category = m_oAllElement[i]->getCategory();
        CGameElement* t_pEelment = m_oAllElement[i];
        switch (category)
        {
        case CGameElement::CATEGORY_NPC:
            CNpc* tpNpc = static_cast<CNpc*>(t_pEelment);
            clearNpc(tpNpc, rmode);
            break;
        }

    } 
}

void CGameLogic::clearNpc(CNpc* pNpc, int mode)
{      
    bool hasIn = m_refShowArea->hasIncludeMaster(pNpc->getPosition());
    switch (mode)
    {
    case MODEL_IN:      
        //
        log("MODEL_IN");
        if (!hasIn)
        {
            pNpc->setState(CNpc::STATE_DIE);
        }
        break;
    case MODEL_OUT:
        log("MODEL_OUT");
        if (hasIn)
        {
            pNpc->setState(CNpc::STATE_DIE);
        }         
        break;
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