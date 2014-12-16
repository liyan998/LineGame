#include "GameElement.h"

#include "util/Math.h"

void CNpc::onEnter()
{
    Node::onEnter();


   
    m_iDirect   = liyan998::CMath::getRandom(0, 360);
    m_iStep     = 2;

    m_iCategory = CGameElement::CATEGORY_NPC;
    m_pSp       = Sprite::create("CloseNormal.png");
   // m_pSp->setScale(1.5f);
    addChild(m_pSp);

}

void CNpc::run(float time)
{
    CEnemy::checkWith();
}


void CNpc::setState(int state)
{
    this->m_State = state;

    switch (state){
    case STATE_LIVE:        
        m_pSp->setVisible(true);
        break;
    case STATE_DIE:
        m_pSp->setVisible(false);
        break;
    }
}


void CNpc::released()
{

}