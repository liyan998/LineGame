#include "GameElement.h"

#include "util/Math.h"

#include "GameResMacros.h"

void CNpc::onEnter()
{
    Node::onEnter();


   
    m_iDirect   = liyan998::CMath::getRandom(0, 360);
    m_iStep     = 2;
    m_iCollR = 20;

    m_iCategory = CGameElement::CATEGORY_NPC;
    //m_pSp       = Sprite::create("CloseNormal.png");
   // m_pSp->setScale(1.5f);
    //addChild(m_pSp);

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_DYB,
        RES_ANIMA_PLS_DYB,
        RES_ANIMA_JSO_DYB
        );

    m_pSp = Armature::create("DYB_Walk");
    m_pSp->getAnimation()->playByIndex(0);
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
        //m_pSp->setVisible(true);
        log("LIVE");
        break;
    case STATE_DIE:
        log("DIE");
       // m_pSp->setVisible(false);
      
        removeChild(m_pSp);
        break;
    }
}


void CNpc::released()
{

}

void CNpc::print(DrawNode* dn)
{
    CEnemy::print(dn);
    
}