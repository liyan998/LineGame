#include "GameElement.h"

#include <cstring>
#include "util/Math.h"

#include "GameResMacros.h"


bool CNpc::init()
{
    Node::init();

    m_iCategory = CGameElement::CATEGORY_NPC;
    m_pArmature       = nullptr;

    m_iDirect   = liyan998::CMath::getRandom(0, 360);
    m_iStep     = 2;
    m_iCollR    = 20;
    m_fCount    = 0.0f;
    m_iReLive   = 3;
    m_iAttick   = 1;


    //m_pSp       = Sprite::create("CloseNormal.png");
    // m_pSp->setScale(1.5f);
    //addChild(m_pSp);




    return true;
}

void CNpc::onEnter()
{
    Node::onEnter();   
    animation_reBack();
}

void CNpc::run(float time)
{
    //log("%d  m_fCount:%f", m_State, m_fCount);
    switch (m_State)
    {
    case STATE_LIVE:
        CEnemy::checkWith();
        break;
    case STATE_REBACK://
        //            
        m_fCount += time;
        if (m_fCount >= m_iReLive)
        {
            m_fCount = 0.0f;
            animation_reBack();
        }
        break;
    default:
        break;
    }
}


void CNpc::setState(int state)
{
    this->m_State = state;

    switch (state){
    case STATE_LIVE:
        log("LIVE");
        animation_move();
        break;
    case STATE_DIE:
        log("DIE");          
        animation_Die();
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

inline
void CNpc::animation_Die()
{
    CGameElement::setCurrentAnimation(ARMATURE_GUARD_DIE_REVIVE);
    m_pArmature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CNpc::movementCallback));
    m_pArmature->getAnimation()->play(PLAYLAB_GUARD_DIE);
}


inline
void CNpc::animation_move()
{   
    CGameElement::setCurrentAnimation(ARMATURE_DYB_WALK);
    m_pArmature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CNpc::movementCallback));
    m_pArmature->getAnimation()->play(PLAYLAB_DYB_FRONT_WALK);
}

inline
void CNpc::animation_reBack()
{
    CGameElement::setCurrentAnimation(ARMATURE_GUARD_DIE_REVIVE);
    m_pArmature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CNpc::movementCallback));
    m_pArmature->getAnimation()->play(PLAYLAB_GUARD_REVIVE);
}


void CNpc::movementCallback(Armature * armature, MovementEventType type,const std::string& name)
{
    //log("type %d  name:%s", type, name.c_str());  
    if (type == MovementEventType::COMPLETE)
    {
        if (strcmp(name.c_str(), PLAYLAB_GUARD_DIE) == 0)
        {
            CGameElement::clearCurrentAnimation();
            CEnemy::randPosition();
            m_fCount = 0.0f;
            setState(STATE_REBACK);        
        }
        else if (strcmp(name.c_str(),PLAYLAB_GUARD_REVIVE) == 0)
        {
            setState(STATE_LIVE);      
        }
    }
}


void CNpc::changeDirect(int direct)
{



}
