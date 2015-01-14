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

    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_BOSSSKILL_ATTICAKOVER, this);

    return true;
}


void CDragon::released()
{
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_BOSSSKILL_ATTICAKOVER, this);
}


void CDragon::onEnter()
{
    CBoss::onEnter();

    //---------------------------------------------

    T_SkillDragonLighing* skilllight = new T_SkillDragonLighing();
    skilllight->m_fMaxTime = 10;   
    skilllight->init();

    T_RandSkill allRandSkill[] = {
        { 3, 0, Skill::SKILL_T_LIGHTING, RandSkill_State::RANDSKILL_STATE_CD, (T_SkillData*)skilllight }
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

    int t_direct = CPath::DIRECT[CMath::getRandom(0, 3)][0];
    m_iDirect = t_direct + CMath::getRandom(-30, 30);
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
    case EVENT_BOSSSKILL_ATTICAKOVER:
       // m_refPlayer->animation_attack();
        skillLightEnd();
       
        break;
    default:
        break;
    }
}


void CDragon::randSkillRelease(float time)
{
    //log("m_iSkillCd:%f", m_fCount);
    switch (m_pRandSkill->m_iSkillId)
    {
    case Skill::SKILL_T_LIGHTING:
        skillLight(time);
        break;
    }
}


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
                //¼õÉË £¬ÊÍ·ÅÉÁµç£¬ÏûÊ§ÔÆ²Ê  

                CEventDispatcher::getInstrance()->dispatchEvent(EVENT_BOSSSKILL_ATTICAK, 0);

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

void CDragon::skillLightEnd()
{
    log("Skill destory!");

    m_refPlayer->destoryLightAttick();

    CEventDispatcher::getInstrance()->dispatchEvent(EVENT_BOSSSKILL_END, new int(m_pRandSkill->m_iSkillId));
    m_pRandSkill->m_iSkillState = RANDSKILL_STATE_CD;
    m_pRandSkill->init();

    createSkillTimer();
}

void CDragon::movementCallback(Armature * armature, MovementEventType type, const std::string& name)
{
    if (type == MovementEventType::COMPLETE)
    {
        if (strcmp(name.c_str(), PLAYLAB_DRAGON_MAGIC_SDY) == 0)
        {
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
        if (strcmp(t_str.c_str() , PLAYLAB_DRAGON_MAGIC_SDY) == 0)
        {
            return;
        }
        getArmature()->getAnimation()->play(it->second);
    }
}