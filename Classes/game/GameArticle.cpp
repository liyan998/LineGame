#include "GameElement.h"

#include "EventSystem.h"
#include "GameResMacros.h"

bool CGameArticle::init()
{
    Node::init();

    m_iCategory = CGameElement::CATEGORY_AWARD;
    m_iCollR    = 20;
    



    return true;
}

void CGameArticle::run(float time)
{

    m_fCount += time;

    if (m_fCount >= 1)
    {
        //log("time to up");
        action_create();
        action_Disp();
        m_fCount = 0.0F;
    }

}


void CGameArticle::print(DrawNode* dn)
{
    switch (m_State)
    {
    case STATE_ACTIVE:
    CGameElement::print(dn);
        break;
    default:
        break;
    }
}

void CGameArticle::setState(int state)
{
    this->m_State = state;

    switch (state)
    {
    case STATE_ACTIVE:
        randPosition();
        setCurrentAnimation(ARMATURE_PROPERTY);
        //m_pSp->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CGameArticle::movementCallback));
        m_pSp->getAnimation()->play(PLAYLAB_PROPERTY_ADDHEALTH);
        break;
    case STATE_DISP:
        log("GameArticle dispter");
        clearCurrentAnimation();
        break;
    case STATE_EFFE:
        //animation_effe();
        break;
    default:
        break;
    }


}

void CGameArticle::animation_effe()
{   
    clearCurrentAnimation();
    setCurrentAnimation(ARMATURE_GUARD_DIE_REVIVE);
    m_pSp->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CGameArticle::movementCallback));
    m_pSp->getAnimation()->play(PLAYLAB_GUARD_REVIVE);
}

void CGameArticle::released()
{

}

void CGameArticle::action_create()
{
    if (m_State != CGameArticle::STATE_DISP)
    {
        return;
    }

    if (m_iTimeCreate++ >= TIME_CREATE_ARTICLE)
    {
        setState(STATE_ACTIVE);
        m_iTimeCreate = 0;
    }
}


void CGameArticle::action_Disp()
{
    if (m_State != STATE_ACTIVE)
    {
        return;
    }
  

    if (m_iTimeDis++ >= TIME_DIS_ARTICLE)
    {
        setState(STATE_DISP);
        m_iTimeDis = 0;
    }

}


void CGameArticle::movementCallback(Armature * armature, MovementEventType type, const std::string& name)
{
    switch (type)
    {
    case MovementEventType::COMPLETE:

    
    if (strcmp(name.c_str(), PLAYLAB_GUARD_REVIVE)==0)
    {
        float* pTf = new float(0.3f);
        CEventDispatcher::getInstrance()->dispatchEvent(EVENT_PRORETY_ADDHEALTH, pTf );
        setState(STATE_DISP);
    }

        break;
    }
}