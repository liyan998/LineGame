#include "GameElement.h"

#include <cstring>
#include "util/Math.h"

#include "GameResMacros.h"
#include "Skill.h"

bool CNpc::init()
{
    Node::init();

    m_iCategory = CGameElement::CATEGORY_NPC;
 

    m_iDirect   = liyan998::CMath::getRandom(0, 360);
    m_iStep     = 2;
    m_iCollR    = 20;
    m_fCount    = 0.0f;
    m_iReLive   = 3;
    m_iAttick   = 1;

    m_iSkillConfuseState = SkillConfuseState::SKILLSTATE_NONE;
    m_iSkillConfuseCount = 0;

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_COOLKING_MAGIC_EFFIE,
        RES_ANIMA_PLS_COOLKING_MAGIC_EFFIE,
        RES_ANIMA_JSO_COOLKING_MAGIC_EFFIE
        );


    //m_pSp       = Sprite::create("CloseNormal.png");
    //m_pSp->setScale(1.5f);
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
    //log("onAri!!!!!!!!!!!!!!!");
    checkSkillConfuse(time);
  
}

void CNpc::checkSkillConfuse(float time)
{
    if (m_iSkillConfuseState != SkillConfuseState::SKILLSTATE_ONAIR)
    {
        return;
    }
    
    m_fCount += time;
    if (m_fCount >= 1)
    {
        if (m_iSkillConfuseCount >= 100)
        {
            m_iSkillConfuseCount = 0;
            setPlayerSkillConfuse(SkillConfuseState::SKILLSTATE_NONE);
            return;
        }

        m_iSkillConfuseCount++;
        m_fCount = 0;
    }
}




void CNpc::changeLiveDie(float time)
{
    switch (m_State)
    {
    case STATE_LIVE:
        CEnemy::checkWithAttick();
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
        setPlayerSkillConfuse(SkillConfuseState::SKILLSTATE_NONE);
        animation_Die();
        
        break;
    }
}

bool CNpc::hasCollWithPlayer()
{
    switch (m_iSkillConfuseState)
    {
    //case SkillConfuseState::SKILLSTATE_NONE:
    case SkillConfuseState::SKILLSTATE_ANIMA:
    case SkillConfuseState::SKILLSTATE_ONAIR:
        return false;

    default:
        break;
    }

    return true;
}

void CNpc::released()
{
   
}

void CNpc::print(DrawNode* dn)
{
    CEnemy::print(dn);
    

    if (m_iSkillConfuseState == SkillConfuseState::SKILLSTATE_ONAIR)
    {
        Vec2 tp = getPosition();
        tp.x = tp.x + 10;
        tp.y = tp.y + 10;
        dn->drawDot(tp, 4, Color4F(1,0,0.4,1));
    }
}

inline
void CNpc::animation_Die()
{
    CGameElement::setCurrentAnimation(ARMATURE_GUARD_DIE_REVIVE);
    getArmature()->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CNpc::movementCallback));
    getArmature()->getAnimation()->play(PLAYLAB_GUARD_DIE);
}



void CNpc::animation_move()
{   
//     CGameElement::setCurrentAnimation(ARMATURE_DYB_WALK);
//     getArmature()->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CNpc::movementCallback));
//     getArmature()->getAnimation()->play(PLAYLAB_DYB_FRONT_WALK);
}

inline
void CNpc::animation_reBack()
{
    CGameElement::setCurrentAnimation(ARMATURE_GUARD_DIE_REVIVE);
    getArmature()->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CNpc::movementCallback));
    getArmature()->getAnimation()->play(PLAYLAB_GUARD_REVIVE);
}



//÷È»ó¼¼ÄÜ
void CNpc::animation_confuse()
{
    CAnimationAxis* aa = findCreateByIndex(INDEX_NPCINDEX_CONFUES);

    aa->setCurrentAnimation(ARMATURE_COOKING_MAGIC_EFFIE);
    aa->getArmature()->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CNpc::movementCallback));
    aa->getArmature()->getAnimation()->play(PLAYLAB_COOLKING_MAGIC_EFFIE);
}


void CNpc::movementCallback(Armature * armature, MovementEventType type,const std::string& name)
{
    //log("type %d  name:%s", type, name.c_str());  
    if (type == MovementEventType::COMPLETE)
    {
        if (strcmp(name.c_str(), PLAYLAB_GUARD_DIE) == 0)
        {
            CGameElement::clearCurrentAnimation();

            Vec2 cp;
            CEnemy::randPosition(cp);
            setPosition(cp);

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

void CNpc::setPlayerSkillConfuse(int state)
{    
    m_iSkillConfuseState = state;

    switch (m_iSkillConfuseState)
    {
    case SkillConfuseState::SKILLSTATE_ONAIR:
        animation_confuse();
        break;
    case SkillConfuseState::SKILLSTATE_NONE:
        CAnimationAxis* aa = findCreateByIndex(INDEX_NPCINDEX_CONFUES);
        aa->clearCurrentAnimation();
        removeChild(aa);
        break;
    }
}