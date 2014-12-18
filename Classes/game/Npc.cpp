#include "GameElement.h"

#include <cstring>
#include "util/Math.h"

#include "GameResMacros.h"


bool CNpc::init()
{
    Node::init();

    m_iCategory = CGameElement::CATEGORY_NPC;
    m_pSp       = nullptr;

    m_iDirect   = liyan998::CMath::getRandom(0, 360);
    m_iStep     = 2;
    m_iCollR    = 20;
    m_fCount    = 0.0f;
    m_iReLive   = 3;


    //m_pSp       = Sprite::create("CloseNormal.png");
    // m_pSp->setScale(1.5f);
    //addChild(m_pSp);

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_DYB,
        RES_ANIMA_PLS_DYB,
        RES_ANIMA_JSO_DYB
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_PIPI_DIE,
        RES_ANIMA_PLS_PIPI_DIE,
        RES_ANIMA_JSO_PIPI_DIE
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_EFFE_DIEREBACK,
        RES_ANIMA_PLS_EFFE_DIEREBACK,
        RES_ANIMA_JSO_EFFE_DIEREBACK
        );


    return true;
}

void CNpc::onEnter()
{
    Node::onEnter();


   
   
    animation_reBack();
    //setState(STATE_LIVE);

}

void CNpc::run(float time)
{
    //log("%d  m_fCount:%f", m_State, m_fCount);
    switch (m_State)
    {
    case STATE_LIVE:
        CEnemy::checkWith();
        break;
    case STATE_REBACK:
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
    //CEnemy::print(dn);
    
}

inline
void CNpc::animation_Die()
{
    setCurrentAnimation("Guard_Die_Revive");    
    m_pSp->getAnimation()->play("Guard_Die");
}


inline
void CNpc::animation_move()
{   
    setCurrentAnimation("DYB_Walk");    
    m_pSp->getAnimation()->playByIndex(0);
}

inline
void CNpc::animation_reBack()
{
    setCurrentAnimation("Guard_Die_Revive");
    m_pSp->getAnimation()->play("Guard_Revive");
}


void CNpc::movementCallback(Armature * armature, MovementEventType type,const std::string& name)
{
    log("type %d  name:%s", type, name.c_str());
  
    if (type == MovementEventType::COMPLETE)
    {
        if (strcmp(name.c_str(), "Guard_Die") == 0)
        {
            clearCurrentAnimation();        
            CEnemy::randPosition();
            m_fCount = 0.0f;
            setState(STATE_REBACK);        
        }
        else if (strcmp(name.c_str(),"Guard_Revive")== 0)
        {
            setState(STATE_LIVE);

      
        }
    }
}


void CNpc::changeDirect(int direct)
{



}

inline
void CNpc::setCurrentAnimation(const char* arname)
{
    if (
        m_pSp != nullptr && 
        strcmp(arname, m_pSp->getAnimation()->getCurrentMovementID().c_str()) == 0
        )
    {
        return;
    }

    clearCurrentAnimation();
    m_pSp = Armature::create(arname);
    m_pSp->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CNpc::movementCallback));
    addChild(m_pSp);
}

inline
void CNpc::clearCurrentAnimation()
{
    if (m_pSp != nullptr)
    {
        m_pSp->getAnimation()->setMovementEventCallFunc(this, nullptr);
        removeChild(m_pSp);
        m_pSp = nullptr;
    }
}