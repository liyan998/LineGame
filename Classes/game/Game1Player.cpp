
#include "GameElement.h"

#include "util/Math.h"
#include "util/Util.h"

// #include "MySprite.h"
#include "GameResMacros.h"
#include "Skill.h"

using namespace liyan998;
using namespace cocostudio;

bool CGamePlayer::init()
{
    Node::init();

    m_iStep                 = 2;
    m_iCollR                = 20;
    m_bFlow                 = false;
    m_oPlayerPosition       = Vec2::ZERO;
    m_pEventAddSpeed        = nullptr;
    m_iEffectAddProtect     = EFFECT_NONE;
    m_iEffectAddSpeed       = EFFECT_NONE;

    m_bHasLight             = false;
    m_pCurrentAnim          = nullptr;

    m_iTornadoColor         = TornadoColor::COLOR_NONE;

    m_iSkillConfuseState    = SKILLSTATE_NONE;
    m_iSkillConfuseCount    = 2;
    m_iSkillTimeCount       = 0;


    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_DRAGON_SKILL_YUN,
        RES_ANIMA_PLS_DRAGON_SKILL_YUN,
        RES_ANIMA_JSO_DRAGON_SKILL_YUN
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_DRAGON_SKILL_YUNRELEAS,
        RES_ANIMA_PLS_DRAGON_SKILL_YUNRELEAS,
        RES_ANIMA_JSO_DRAGON_SKILL_YUNRELEAS
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_PIPI_HIT,
        RES_ANIMA_PLS_PIPI_HIT,
        RES_ANIMA_JSO_PIPI_HIT
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_COOLKING_HIT,
        RES_ANIMA_PLS_COOLKING_HIT,
        RES_ANIMA_JSO_COOLKING
        );
    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_COOLKING_MAGIC,
        RES_ANIMA_PLS_COOLKING_MAGIC,
        RES_ANIMA_JSO_COOLKING_MAGIC
        );
    //-------------------------------------------

    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_PROPERTY_ADDSPEED, this);
    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_PROPERTY_ADDPROTECT, this);
    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_BOSSSKILL_START, this);
    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_BOSSSKILL_END, this);

    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_BOSSSKILL_LIIGHTATTICAK, this);
    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_BOSSSKILL_LIGHTCOUNT, this);

    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_BOSSSKILL_TORNADO_CHANAGE, this);

    //-----------------------------------------------------
    
    animation_idle();
                                  
    //------------------------------------------------

    setState(STATE_STOP); 

    m_oDirectTab.insert(std::pair<int, const char*>(ANGLE_DOWN,     PLAYLAB_COOLKING_WALK_FRONT));
    m_oDirectTab.insert(std::pair<int, const char*>(ANGLE_UP,       PLAYLAB_COOLKING_WALK_BACK));
    m_oDirectTab.insert(std::pair<int, const char*>(ANGLE_LEFT,     PLAYLAB_COOLKING_WALK_LEFT));
    m_oDirectTab.insert(std::pair<int, const char*>(ANGLE_RIGHT,    PLAYLAB_COOLKING_WALK_RIGHT));

    return true;
}


void CGamePlayer::released()
{
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_PROPERTY_ADDSPEED, this);
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_PROPERTY_ADDPROTECT, this);

    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_BOSSSKILL_START, this);
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_BOSSSKILL_END, this);

    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_BOSSSKILL_LIIGHTATTICAK, this);
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_BOSSSKILL_LIGHTCOUNT, this);

    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_BOSSSKILL_TORNADO_CHANAGE, this);

    this->removeAllChildren();
}

void CGamePlayer::setPlayerPosition(const Vec2& pos)
{                      
    Vec2 tp = pos; 
    CUtil::formartGrid(tp, getStep());
    m_oPlayerPosition = tp;


    //getArmature()->setPosition(tp);


   
    if (m_pCurrentAnim != nullptr)
    {
        m_pCurrentAnim->getArmature()->setAnchorPoint(Vec2(0.5f, 0.2f));
        m_pCurrentAnim->setPosition(m_oPlayerPosition);
    }

    if (m_bHasLight)
    {
        setLigitPosition(tp);
    }

}


const Vec2& CGamePlayer::getPlayerPosition()
{
    //return getArmature()->getPosition();
    return m_oPlayerPosition;
}


void CGamePlayer::setLigitPosition(const Vec2& inPos)
{
    CAnimationAxis* pAa = (CAnimationAxis*)getChildByTag(TagIndex::Anim_Light);

    Vec2 nInpos(inPos.x , inPos.y + 100);

    pAa->setPosition(nInpos);
}

/************************************************************************/
/* 
@brief          设置目标位置
@param[in]      inpoint 被检测坐标
@param[out]
@return         void

*/
/************************************************************************/
void CGamePlayer::setTarget(const Vec2& point)
{  
    m_oCurrentTarget = point; 
    
    if (m_State != STATE_RUN)
    {
        setState(STATE_RUN);
    }
}


void CGamePlayer::checkPosition(const Vec2& inPoint)
{      
    if (m_State == STATE_STOP && getPlayerPosition() != inPoint)
    {
        setTarget(inPoint);
    }         
}



int CGamePlayer::getStrackSize()
{                          
    return m_oAllGuide.size();
}

void CGamePlayer::addFollow(const Vec2& point)
{       
//     if (m_State == STATE_RUN)
//     {
        m_oAllGuide.push_back(point);
        log("+  add Target point %f,%f", point.x, point.y);
//         return;
//     }
/*    log("not target");*/
}


void CGamePlayer::backFollow()
{
    if (m_oAllGuide.size() > 0)
    {
        m_oAllGuide.erase(m_oAllGuide.end() - 1);
    }
}


int CGamePlayer::getStep()
{                       
    int step = this->m_iStep;

    if (m_iTornadoColor != TornadoColor::COLOR_NONE)
    {
        switch (m_iTornadoColor)
        {
        case TornadoColor::COLOR_BLACK:
            step = 1;
            break;
        case TornadoColor::COLOR_WHITE:
            step = GRAD_NUMBER(m_iStep * 2);
            break;
        default:
            break;
        }
    }

    //log("PLayer step:%d", step);

    if (m_iEffectAddSpeed == Effect::EFFECT_ADDSPEED)
    {
//         float tf = m_iStep * m_pEventAddSpeed->addPart;
        step = GRAD_NUMBER(m_iStep * 2);
        //log("step : %d %f", step);
        //step = GRAD_NUMBER(step);
    }

    return step;
}

void CGamePlayer::run(float time)
{

    //log("-------------------------------");
	//log("plyer urn %d ,%d", m_State ,m_oAllGuide.size());
    switch (m_State)
    {
    case STATE_RUN:   
        playerRun(time);                                          
        break;
    case STATE_STANDER:
        playerStander(time);
        break;
    case STATE_STOP:    
        if (m_oAllGuide.size() > 0)
        {
            setTarget(m_oAllGuide[0]);
        }    
        break;
    }

    m_fCount += time;
    if (m_fCount >= 1)
    {
        checkSkillConnfuse();
        checkEffect();
        m_fCount = 0;
    }

}

void CGamePlayer::playerStander(float time)
{
    if (m_oAllGuide.size() < 1)
    {
        setState(STATE_STOP);
        return;
    }

    Vec2 lasTarget = *m_oAllGuide.begin();

    if (m_oCurrentTarget == lasTarget)
    {
        log("- RemoveTarget:%f,%f", lasTarget.x, lasTarget.y);

        m_refSp->addRoad(lasTarget);

        m_oAllGuide.erase(m_oAllGuide.begin());
    }

    if (m_oAllGuide.size() < 1)
    {
        return;
    }
    setTarget(m_oAllGuide[0]);
}



void CGamePlayer::playerRun(float time)
{
    int dis = ccpDistance(getPlayerPosition(), m_oCurrentTarget);

    //log("%d  target:%f,%f", dis, m_oCurrentTarget.x, m_oCurrentTarget.y);
    if (dis < getStep())
    {
        setState(STATE_STANDER);
        return;
    }

    int t_direct = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(getPlayerPosition(), m_oCurrentTarget)));
    changeDirect(t_direct);

    m_iCurrentDirect = t_direct;

    Vec2 npos = CMath::getVec2(getPlayerPosition(), getStep(), CMath::angleToRadian(m_iCurrentDirect));
    CUtil::formartGrid(npos, getStep());
    //CUtil::formartGrid(npos);

    setPlayerPosition(npos);
}


void CGamePlayer::changeDirect(int angle)
{
    if (angle != m_iAnimDirect)
    {         
         m_iAnimDirect = angle;
         log("current Direct:%d", m_iAnimDirect);
        std::map<int, const char*>::iterator it = m_oDirectTab.find(angle);

        if (it != m_oDirectTab.end())
        {
            m_pCurrentAnim->getArmature()->getAnimation()->play(it->second);
        }
    }
}

void CGamePlayer::print(DrawNode* dn)
{    
    if (m_iEffectAddSpeed == EFFECT_ADDSPEED)
    {    
        dn->drawDot(getPlayerPosition(), 10, Color4F(1,0,1,0.6)); 
    }

    if (m_iEffectAddProtect == EFFECT_ADDPROTECTED)
    {
        Vec2 tPos = getPlayerPosition();
        tPos.x += 10;
        dn->drawDot( tPos, 10, Color4F(1, 1, 1, 0.6));
    }

    dn->drawDot(getPlayerPosition(), getCollwithR(), Color4F(1, 0, 1,0.21));
  
}

void CGamePlayer::setState(int state)
{
    this->m_State = state;
    switch (state)
    {
    case STATE_RUN:
        log("Player is MoveSTATE!");
        animation_move();
        break;
    case STATE_STANDER:
        //m_oAllGuide.clear();
        m_iAnimDirect = ANGLE_NONE;
        log("Player is Stander");  
        animation_idle();
        break;
    case STATE_STOP:   
        m_iAnimDirect = ANGLE_NONE;
        m_oAllGuide.clear();
        log("Player is Stop");
        animation_idle();
        break;
    case STATE_DIE:
        m_oAllGuide.clear();
        animation_die();
        break;
    default:
        break;
    }
}


void CGamePlayer::fixTargetPostion(const Vec2& inResPosition, const Vec2& inTargetPostion)
{
    if (inResPosition == m_oCurrentTarget)
    {
        m_oCurrentTarget = inTargetPostion;    
        log("m_oCurrentTarget Target is Update");
        return;
    }

    //----------------------------------------------

    for (int i = 0; i < m_oAllGuide.size();i++)
    {                                  
        if (m_oAllGuide[i] == inResPosition)
        {
            m_oAllGuide[i] = inTargetPostion;
            log("m_oAllGuide Target is Update");
            return;
        }
    }
}




void CGamePlayer::animation_attack()
{   
//     setCurrentAnimation(ARMATURE_PIPI_HIT);
//     getArmature()->setAnchorPoint(Vec2(0.5f, 0.2f));
//     getArmature()->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CGamePlayer::movementCallback));
//     getArmature()->getAnimation()->playByIndex(0);
//     setPlayerPosition(m_oPlayerPosition);

   
//     if (m_pCurrentAnim != nullptr)
//     {
//         removeChild(m_pCurrentAnim);
//         m_pCurrentAnim = nullptr;
//     }

//     CAnimationAxis* pAa = findCreateByIndex(Anim_attick);
//     pAa->setCurrentAnimation(ARMATURE_PIPI_HIT);
//     pAa->getArmature()->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CGamePlayer::movementCallback));
//     pAa->getArmature()->getAnimation()->playByIndex(0);
//     m_pCurrentAnim = pAa;
//    setPlayerPosition(getPlayerPosition());


    CAnimationAxis* pAa = findCreateByIndex(Anim_idle);
    pAa->getArmature()->getAnimation()->play(PLAYLAB_COOLKING_HIT);

    //setPlayerPosition(getPlayerPosition());

}

void CGamePlayer::animation_idle()
{    
//     setCurrentAnimation(ARMATURE_PIPI_STANDER);
//     getArmature()->setAnchorPoint(Vec2(0.5f, 0.2f));
//     getArmature()->getAnimation()->playByIndex(0);
// 
//     setPlayerPosition(m_oPlayerPosition);

//     if (m_pCurrentAnim != nullptr)
//     {
//         removeChild(m_pCurrentAnim);
//     }

    CAnimationAxis* pAa = findCreateByIndex(Anim_idle);

    if (m_pCurrentAnim == nullptr 
        || 
        strcmp(pAa->getArmature()->getAnimation()->getCurrentMovementID().c_str(), PLAYLAB_COOLKING_STANDER_FRONT) != 0)
    {
        pAa->setCurrentAnimation(ARMATURE_COOLKING);
        pAa->getArmature()->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CGamePlayer::movementCallback));
        m_pCurrentAnim = pAa;
        setPlayerPosition(getPlayerPosition());

    }

    pAa->getArmature()->getAnimation()->play(PLAYLAB_COOLKING_STANDER_FRONT);
}

void CGamePlayer::animation_magic()
{
    CAnimationAxis* pAa = findCreateByIndex(Anim_idle);

    if (pAa != nullptr 
        &&         
        strcmp(pAa->getArmature()->getAnimation()->getCurrentMovementID().c_str(), ARMATURE_COOKING_MAGIC) != 0
        )
    {
        pAa->setCurrentAnimation(ARMATURE_COOKING_MAGIC);
        pAa->getArmature()->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CGamePlayer::movementCallback));
        pAa->getArmature()->getAnimation()->playByIndex(0);
    }

}


//TODO 完成动画
void CGamePlayer::animation_die()
{
    m_pCurrentAnim->getArmature()->getAnimation()->play(PLAYLAB_COOLKING_DIE);
}

//TODO 完成动画
void CGamePlayer::animation_move()
{
    CAnimationAxis* pAa = findCreateByIndex(Anim_idle);
    pAa->getArmature()->getAnimation()->play(PLAYLAB_COOLKING_WALK_FRONT);

}


void CGamePlayer::checkEffect()
{
    if (m_iEffectAddSpeed == Effect::EFFECT_ADDSPEED)
    {
        if (m_pEventAddSpeed->time-- <= 0)
        {
            m_iEffectAddSpeed = Effect::EFFECT_NONE;

            delete m_pEventAddSpeed;
            m_pEventAddSpeed = nullptr;
        }
    }
}


void CGamePlayer::actionEvent(int eventid, EventParm pData)
{
    switch (eventid)
    {
    case EVENT_PROPERTY_ADDSPEED:
        h_actionAddSpeed(pData);
        break;
    case EVENT_PROPERTY_ADDPROTECT:
        h_actionAddProtect(pData);
        break;
    case EVENT_BOSSSKILL_END:
        h_actionSkillEnd(pData);
        break;
    case EVENT_BOSSSKILL_START:
        h_actionSkillStart(pData);
        break;
    case EVENT_BOSSSKILL_LIIGHTATTICAK:
        h_actionSkillAttick(pData);
        break;
    case EVENT_BOSSSKILL_LIGHTCOUNT:
        h_actionSkillLightCount(pData);
        break;
    case EVENT_BOSSSKILL_TORNADO_CHANAGE:
        h_actionSkillTornadoColor(pData);
        break;
    default:
        break;
    }
}


void CGamePlayer::h_actionSkillTornadoColor(EventParm pData)
{
    m_iTornadoColor = *(int*)pData;    
}

void CGamePlayer::h_actionAddProtect(EventParm pData)
{
    m_iEffectAddProtect = Effect::EFFECT_ADDPROTECTED;
}

bool CGamePlayer::hasInProtected()
{
    if (m_iEffectAddProtect == EFFECT_ADDPROTECTED)
    {
        return true;
    }
    return false;
}

void CGamePlayer::setProtectReleased()
{
    this->m_iEffectAddProtect = Effect::EFFECT_NONE;
}


void CGamePlayer::h_actionAddSpeed(EventParm pData)
{
    struct T_EventPropertyAddSpeed* pEffAdd = (struct T_EventPropertyAddSpeed*)pData;

    m_pEventAddSpeed    = T_EventPropertyAddSpeed::clone(pEffAdd);
    m_iEffectAddSpeed   = Effect::EFFECT_ADDSPEED;
}

void CGamePlayer::h_actionSkillEnd(EventParm pData)
{
//     CAnimationAxis* pAa = (CAnimationAxis*)getChildByTag(TagIndex::Anim_Light);
//     pAa->getArmature()->getAnimation()->stop();
//     removeChild(pAa);

    //m_bHasLight = false;
    int skillid = *(int*)pData;

    switch (skillid)
    {
    case CBoss::Skill::SKILL_T_TORNADO:
        m_iTornadoColor = TornadoColor::COLOR_NONE;
        break;
    case CBoss::Skill::SKILL_T_LIGHTING:
       // animation_attack();
        break;
    default:
        break;
    }

    
}

void CGamePlayer::h_actionSkillStart(EventParm pData)
{
    T_RandSkill* tpRand = (*(T_RandSkill**)pData);
    int skillid = tpRand->m_iSkillId;

    switch (skillid)
    {
    case CDragon::Skill::SKILL_T_LIGHTING:
        setLightAttack(true);
        break;
    case CBoss::Skill::SKILL_T_TORNADO:
        T_SkillDrogTornado* tpSDT = (T_SkillDrogTornado*)tpRand->m_pSkill;
        m_iTornadoColor = tpSDT->currentColor;
        break;
    }
}

void CGamePlayer::h_actionSkillAttick(EventParm pData)
{    
    setLightAttickReleased();
}

void CGamePlayer::movementCallback(Armature * armature, MovementEventType type, const std::string& name)
{   
    if (type == MovementEventType::COMPLETE)
    {
        if (strcmp(name.c_str(), PLAYLAB_DRAGON_SKILL_YUNRELEAS) == 0)
        {
            //destoryLightAttick();
            //animation_attack();            
            CEventDispatcher::getInstrance()->dispatchEvent(EVENT_BOSSSKILL_LIGHTATTICAKOVER, 0);

        }
//         else if (strcmp(name.c_str(), PLAYLAB_PIPI_HIT) == 0)
//         {
//             animation_idle();      
//         }
        else if (strcmp(name.c_str(), PLAYLAB_COOLKING_HIT) == 0)
        {
            animation_idle();
        }else if (strcmp(name.c_str(), PLAYLAB_COOLKING_DIE) == 0)
        {
            CEventDispatcher::getInstrance()->dispatchEvent(EVENT_PLAYERDIE, PARM_NULL);
        }
        else if (strcmp(name.c_str(), PLAYLAB_COOLKING_MACICACTION) == 0)
        {
            m_iSkillConfuseCount--;
            m_iSkillConfuseState = SkillConfuseState::SKILLSTATE_ONAIR;
            CEventDispatcher::getInstrance()->dispatchEvent(EVENT_PLAYERSKILL_CONFUSE, new int(m_iSkillConfuseState));
            animation_idle();
        }
    }
}


void CGamePlayer::h_actionSkillLightCount(EventParm pData)
{
    int count = *((int*)pData);
    
    setLightAttackCount(count);
}



/////////////////////////////////////////////////////////////////
//遭遇闪电攻击
////////////////////////////////////////////////////////////////
void CGamePlayer::setLightAttack(bool lightAttack)
{
    this->m_bHasLight = lightAttack;
    log("setLightAttack:%d", lightAttack);
    if (this->m_bHasLight)
    {
        log("light Attick~~~");
        CAnimationAxis* pAa = (CAnimationAxis*)getChildByTag(TagIndex::Anim_Light);
        if (pAa == nullptr)
        {
            pAa = CAnimationAxis::create();
            pAa->setTag(TagIndex::Anim_Light);
            addChild(pAa);
            setLigitPosition(getPlayerPosition());
        }

        pAa->setCurrentAnimation(ARMATURE_DRAGON_SKILL_YUN);
        pAa->getArmature()->getAnimation()->playByIndex(0);
    }
}


void CGamePlayer::setLightAttickReleased()
{
    if (m_bHasLight)
    {
        CAnimationAxis* pAa = (CAnimationAxis*)getChildByTag(TagIndex::Anim_Light);
        pAa->setCurrentAnimation(ARMATURE_DRAGON_SKILL_YUNRELEAS);
        pAa->getArmature()->getAnimation()->setMovementEventCallFunc(pAa, movementEvent_selector(CGamePlayer::movementCallback));
        pAa->getArmature()->getAnimation()->playByIndex(0);
    }
}

void CGamePlayer::setLightAttackCount(int count)
{
    if (!m_bHasLight)
    {
        log("no light skill");
        return;
    }

    CAnimationAxis* pAa = (CAnimationAxis*)getChildByTag(TagIndex::Anim_Light);
    log("count :%d", count);
    Color3B tcolor[] = 
    {
        { 255, 255, 255 },
        { 200, 200, 200 },
        { 102, 102, 102 },
        { 50, 50, 50 }
    };

    if (count > 3)
    {
        setLightAttickReleased();
        return;
    }

    pAa->getArmature()->setColor(tcolor[count]);
}


void CGamePlayer::destoryLightAttick()
{
    if (m_bHasLight)
    {
        CAnimationAxis* pAa = (CAnimationAxis*)getChildByTag(TagIndex::Anim_Light);
        this->removeChild(pAa);

        m_bHasLight = false;
    }
}

//////////////////////////////////////////////////////////////////
//释放魅惑技能
//////////////////////////////////////////////////////////////////
bool CGamePlayer::releasSkill(int skillid)
{
    switch (skillid)
    {
    case SKILL_CONFUSE:
       return releasSkillConfuse();       
    default:
        break;
    }

    return true;
}


bool CGamePlayer::releasSkillConfuse()
{
    if (m_iSkillConfuseState == SkillConfuseState::SKILLSTATE_ANIMA 
        || 
        m_iSkillConfuseState == SkillConfuseState::SKILLSTATE_ONAIR
        )
    {
        return false;
    }

    if (m_iSkillConfuseCount <= 0)
    {
        return false;
    }


    m_iSkillConfuseState = SkillConfuseState::SKILLSTATE_ANIMA;
    log("play magic animation!");
    animation_magic();
    
    return true;
}


void CGamePlayer::checkSkillConnfuse()
{
    if (m_iSkillConfuseState == SkillConfuseState::SKILLSTATE_NONE)
    {
        return;
    }

    if (m_iSkillTimeCount >= 10)
    {
        m_iSkillTimeCount = 0;
        m_iSkillConfuseState = SkillConfuseState::SKILLSTATE_NONE;

        CEventDispatcher::getInstrance()->dispatchEvent(EVENT_PLAYERSKILL_CONFUSE, new int(m_iSkillConfuseState));
        return;
    }

    m_iSkillTimeCount++;
}