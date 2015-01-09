#include "GameElement.h"

bool CDragon::init()
{
    CBoss::init();


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
    setCurrentAnimation(ARMATURE_QINGCAI);
    getArmature()->getAnimation()->playByIndex(0);

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
    if (tpSkilllight->state == 1)
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
                tpSkilllight->state = 1;
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

    //log("%d Skill Time:%f", tpSkilllight->buffer, tpSkilllight->m_fTime);

    if (tpSkilllight->m_fTime < m_fCount)
    {       
        m_fCount = 0;
        skillLightEnd();        
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

    CEventDispatcher::getInstrance()->dispatchEvent(EVENT_BOSSSKILL_END, new int(m_pRandSkill->m_iSkillId));
    m_pRandSkill->m_iSkillState = RANDSKILL_STATE_CD;
    m_pRandSkill->init();

    createSkillTimer();
}