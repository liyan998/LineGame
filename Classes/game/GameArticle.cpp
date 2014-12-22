#include "GameElement.h"

bool CGameArticle::init()
{
    Node::init();

    m_iCategory = CGameElement::CATEGORY_AWARD;
    m_iCollR = 20;
    



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
        break;
    default:
        break;
    }


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