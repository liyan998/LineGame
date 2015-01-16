#include "GameElement.h"

bool CDragon::init()
{
    CBoss::init();

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_DRAGON,
        RES_ANIMA_PLS_DRAGON,
        RES_ANIMA_JSO_DRAGON
        );

    //-----------------------------------------------------------------
    
    m_oAngleTable.insert(std::pair<int, const char*>(ANGLE_DOWN,    PLAYLAB_DRAGON_DOWN_WALK));
    m_oAngleTable.insert(std::pair<int, const char*>(ANGLE_UP,      PLAYLAB_DRAGON_UP_WALK));
    m_oAngleTable.insert(std::pair<int, const char*>(ANGLE_LEFT,    PLAYLAB_DRAGON_LEFT_WALK));
    m_oAngleTable.insert(std::pair<int, const char*>(ANGLE_RIGHT,   PLAYLAB_DRAGON_RIGHT_WALK));

    //--------------------------------------------------------

    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_BOSSSKILL_LIGHTATTICAKOVER, this);
    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_BOSSSKILL_TORNADO_SURROUND, this);

    return true;
}


void CDragon::released()
{
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_BOSSSKILL_TORNADO_SURROUND, this);
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_BOSSSKILL_LIGHTATTICAKOVER, this);
}


void CDragon::onEnter()
{
    CBoss::onEnter();

    //---------------------------------------------

    //风魔龙闪电云技能
    T_SkillDragonLighing* skilllight    = new T_SkillDragonLighing();
    skilllight->m_fMaxTime = 10; //   
    skilllight->init();

    //风魔龙 龙卷风技能
    T_SkillDrogTornado* pSkillTornado   = new T_SkillDrogTornado();
    pSkillTornado->m_fMaxTime = 120;
    pSkillTornado->m_fMAXWhiteTime = 3;
    pSkillTornado->m_fMAXBlackTime = 4;

    pSkillTornado->init();

    //风魔龙 龙卷风技能
    T_RandSkill allRandSkill[] = 
    {
        //{ 3, 0, Skill::SKILL_T_LIGHTING, RandSkill_State::RANDSKILL_STATE_CD, (T_SkillData*)skilllight },
        { 3, 0, Skill::SKILL_T_TORNADO, RandSkill_State::RANDSKILL_STATE_CD, (T_SkillData*)pSkillTornado }
    
    };
    
    int size = sizeof(allRandSkill) / sizeof(allRandSkill[0]);
    for (int i = 0; i < size;i++)
    {
        T_RandSkill* randskill      = new T_RandSkill();

        randskill->m_iMaxCD         = allRandSkill[i].m_iMaxCD;
        randskill->m_iSkillCd       = allRandSkill[i].m_iSkillCd;
        randskill->m_iSkillId       = allRandSkill[i].m_iSkillId;
        randskill->m_iSkillState    = allRandSkill[i].m_iSkillState;
        randskill->m_pSkill         = allRandSkill[i].m_pSkill;

        randskill->init();

        m_oAllRandSkill.push_back(randskill);
    }

    createSkillTimer();
    
    //======================================

    clearCurrentAnimation();    
    setCurrentAnimation(ARMATURE_DRAGON);
    getArmature()->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CDragon::movementCallback));
    getArmature()->getAnimation()->playByIndex(0);

    //-------------------------------------

    int t_direct    = CPath::DIRECT[CMath::getRandom(0, 3)][0];
    m_iDirect       = t_direct + CMath::getRandom(-30, 30);
    changeDirect(t_direct);
}


void CDragon::run(float time)
{
    CBoss::run(time);
}

void CDragon::actionEvent(int eventid, EventParm pData)
{
    switch (eventid)
    {
    case EVENT_BOSSSKILL_LIGHTATTICAKOVER:
       // m_refPlayer->animation_attack();
        skillLightEnd();       
        break;
    case EVENT_BOSSSKILL_TORNADO_SURROUND:
        skillTornadoEnd();
        break;
    default:
        break;
    }
}


void CDragon::movementCallback(Armature * armature, MovementEventType type, const std::string& name)
{
    if (type == MovementEventType::COMPLETE)
    {
        if (strcmp(name.c_str(), PLAYLAB_DRAGON_MAGIC_SDY) == 0)
        {
            CBoss::startRandSkill();
            getArmature()->getAnimation()->play(PLAYLAB_DRAGON_UP_WALK);
        }else if (strcmp(name.c_str(), PLAYLAB_DRAGON_MAGIC_TORNADO) == 0)
        {
            //释放龙卷风技能
            CBoss::startRandSkill();
           
            getArmature()->getAnimation()->play(PLAYLAB_DRAGON_UP_WALK);
        }
    }
}

void CDragon::changeDirect(int direct)
{
    std::map<int, const char*>::iterator it = m_oAngleTable.find(direct);
    if (it != m_oAngleTable.end())
    {
        const std::string& t_str = getArmature()->getAnimation()->getCurrentMovementID();
        if (strcmp(t_str.c_str(), PLAYLAB_DRAGON_MAGIC_SDY) == 0 
            || 
            strcmp(t_str.c_str(), PLAYLAB_DRAGON_MAGIC_TORNADO) == 0)
        {
            return;
        }
        getArmature()->getAnimation()->play(it->second);
    }
}



int CDragon::getAttack()
{
    if (m_iRandSkillState == RandSkill_State::RANDSKILL_STATE_RELEAS
        &&
        m_pRandSkill->m_iSkillId == Skill::SKILL_T_LIGHTING)
    {
        return CBoss::getAttack() * 1.5f;
    }

    return CBoss::getAttack();
}


void CDragon::randSkillRelease(float time)
{
    //log("m_iSkillCd:%f", m_fCount);
    switch (m_pRandSkill->m_iSkillId)
    {
    case Skill::SKILL_T_LIGHTING:
        skillLight(time);
        break;
    case Skill::SKILL_T_TORNADO:
        skillTornado(time);
        break;
    }
}

//////////////////////////////////////////////////////////////////////////////
//风魔龙技能 闪电云
//////////////////////////////////////////////////////////////////////////////
void CDragon::skillLight(float time)
{
    T_SkillDragonLighing* tpSkilllight = (T_SkillDragonLighing*)m_pRandSkill->m_pSkill;
    
    //------------------------------------------------
    if (tpSkilllight->state == 2)
    {
        //log("skill attick");
        return;
    }
    
    tpSkilllight->m_fCount += time;
    if (tpSkilllight->m_fCount >= 1)
    {
        if (m_refSp->hasSkillLightCountTime())
        {
            tpSkilllight->buffer++;
            if (tpSkilllight->buffer > 3)
            {
                //减伤 ，释放闪电，消失云彩  

                CEventDispatcher::getInstrance()->dispatchEvent(EVENT_BOSSSKILL_LIIGHTATTICAK, 0);

                m_refSp->attiack(getAttack(), this);
                //skillLightEnd();
                tpSkilllight->state = 2;
            }
        }
        else
        {
            tpSkilllight->buffer--;
            if (tpSkilllight->buffer <= 0)
            {
                tpSkilllight->buffer = 0;
            }
        }
        
        CEventDispatcher::getInstrance()->dispatchEvent(EVENT_BOSSSKILL_LIGHTCOUNT, new int(tpSkilllight->buffer));
        tpSkilllight->m_fCount = 0;
    }

    //----------------------------------------------

    if (tpSkilllight->m_fTime < m_fCount)
    {       
        m_fCount = 0;
        skillLightEnd();        
    }
}


void CDragon::startRandSkill()
{
    log("tpSkilllight->state+++");

    switch (m_pRandSkill->m_iSkillId)
    {
    case Skill::SKILL_T_LIGHTING:
        getArmature()->getAnimation()->play(PLAYLAB_DRAGON_MAGIC_SDY);
    break;
    case Skill::SKILL_T_TORNADO:
        getArmature()->getAnimation()->play(PLAYLAB_DRAGON_MAGIC_TORNADO);
    break;

    }
}

void CDragon::skillLightEnd()
{
    log("skillLightEnd destory!");

    m_refPlayer->destoryLightAttick();

    CEventDispatcher::getInstrance()->dispatchEvent(EVENT_BOSSSKILL_END, new int(m_pRandSkill->m_iSkillId));
    m_pRandSkill->m_iSkillState = RANDSKILL_STATE_CD;
    m_pRandSkill->init();

    createSkillTimer();
}


////////////////////////////////////////////////////////////
//风魔龙技能 龙卷风
////////////////////////////////////////////////////////////
void CDragon::skillTornado(float time)
{
    T_SkillDrogTornado* tpSkillTornado = (T_SkillDrogTornado*)m_pRandSkill->m_pSkill;

    switch (tpSkillTornado->currentColor)
    {
    case T_SkillDrogTornado::TORNADO_COLOR_BLACK:
        skillTornadoBlack(tpSkillTornado, time);
        break;
    case T_SkillDrogTornado::TORNADO_COLOR_WHITE:
        skillTornadoWhite(tpSkillTornado, time);
        break;
    default:
        break;
    }

    //持续时间结束
    if (m_fCount > 1)
    {
        tpSkillTornado->m_fTime--;
        if (tpSkillTornado->m_fTime <= 0)
        {
            skillTornadoEnd();
        }       
        m_fCount = 0;    
    }
}

void CDragon::skillTornadoEnd()
{
    CEventDispatcher::getInstrance()->dispatchEvent(EVENT_BOSSSKILL_END, new int(m_pRandSkill->m_iSkillId));
    m_pRandSkill->m_iSkillState = RANDSKILL_STATE_CD;
    m_pRandSkill->init();

    createSkillTimer();
}


void CDragon::skillTornadoBlack(T_SkillDrogTornado* pDr, float time)
{
    pDr->m_fBlackTime += time;

    if (pDr->m_fBlackTime >= pDr->m_fMAXBlackTime)
    {
        pDr->currentColor = T_SkillDrogTornado::TORNADO_COLOR_WHITE;

        CEventDispatcher::getInstrance()->dispatchEvent(EVENT_BOSSSKILL_TORNADO_CHANAGE, new int(pDr->currentColor));
        pDr->m_fBlackTime = 0;
    }
}

void CDragon::skillTornadoWhite(T_SkillDrogTornado* pDr, float time)
{
    pDr->m_fWhiteTime += time;

    if (pDr->m_fWhiteTime >= pDr->m_fMAXWhiteTime)
    {
        pDr->currentColor = T_SkillDrogTornado::TORNADO_COLOR_BLACK;

        CEventDispatcher::getInstrance()->dispatchEvent(EVENT_BOSSSKILL_TORNADO_CHANAGE, new int(pDr->currentColor));
        pDr->m_fWhiteTime = 0;
    }
}