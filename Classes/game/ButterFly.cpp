#include "GameElement.h"


bool CButterFly::init()
{
    CBoss::init();


    return true;
}


void CButterFly::onEnter()
{
    Node::onEnter();

    T_SkillBigArea* tPBigArea = new T_SkillBigArea();
    tPBigArea->m_fArea = 3.0f; //面积扩展倍数
    tPBigArea->m_fMaxTime = 10;   //持续时间

    T_SkillFlush* tPFlush = new T_SkillFlush();
    tPFlush->m_iMaxCount = 3;

    //技能的初始化
    T_RandSkill allskill[] =
    {
        { 20, 0, Skill::SKILL_T_BIGAREA, RANDSKILL_STATE_CD, static_cast<T_SkillData*>(tPBigArea) },
        { 15, 0, Skill::SKILL_T_FLUSH, RANDSKILL_STATE_CD, static_cast<T_SkillData*>(tPFlush) }
    };

    for (int i = 0; i < 2; i++)
    {
        T_RandSkill* t_pRskill = new T_RandSkill();

        t_pRskill->m_iMaxCD = allskill[i].m_iMaxCD;
        t_pRskill->m_iSkillId = allskill[i].m_iSkillId;
        t_pRskill->m_iSkillState = allskill[i].m_iSkillState;
        t_pRskill->m_pSkill = allskill[i].m_pSkill;
        t_pRskill->init();

        m_oAllRandSkill.push_back(t_pRskill);
    }

    //--------------------------------------------------------------


    //创建随机技能
    createSkillTimer();

    animation_move();
}


void CButterFly::run(float time)
{
    CBoss::run(time);


}

float CButterFly::getCollwithR()
{
    if (m_iRandSkillState == RandSkill_State::RANDSKILL_STATE_RELEAS
        &&
        m_pRandSkill->m_iSkillId == Skill::SKILL_T_BIGAREA)
    {
        T_SkillBigArea* pTskill = static_cast<T_SkillBigArea*>(m_pRandSkill->m_pSkill);
        return CEnemy::getCollwithR() * pTskill->m_fArea;
    }
    return CEnemy::getCollwithR();
}



bool CButterFly::hasKeepMoveing()
{
    if (m_iRandSkillState == RANDSKILL_STATE_RELEAS)
    {
        switch (m_pRandSkill->m_iSkillId)
        {
        case Skill::SKILL_T_BIGAREA:
        {
                                       Vec2 tP;
                                       switch (m_refSp->getState())
                                       {
                                       case CMySprite::STATE_DRAW:
                                       case CMySprite::STATE_CLOSE:

                                           if (collwithPlayer(getPosition()) || collwithGuide(getPosition(), tP))
                                           {
                                               m_refSp->attiack(getAttack(), this);
                                           }

                                           break;
                                       default:
                                           break;
                                       }
                                       return false;
        }
            break;

        case Skill::SKILL_T_FLUSH:
            return false;
        }
    }

    return true;
}

void CButterFly::animation_move()
{
    CGameElement::setCurrentAnimation(ARMATURE_QINGCAI);
    m_pArmature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CBoss::movementCallback));
    m_pArmature->getAnimation()->playByIndex(0);
}

void CButterFly::releasFlush()
{
    Vec2 cp;
    randPosition(cp);
    setPosition(cp);
}

void CButterFly::randSkillRelease(float time)
{
    //log("m_iSkillCd:%f", m_fCount); 

    switch (m_pRandSkill->m_iSkillId)
    {
    case Skill::SKILL_T_BIGAREA:
    {
                                   T_SkillBigArea* tpSkillBigArea = (T_SkillBigArea*)m_pRandSkill->m_pSkill;
                                   if (m_fCount >= tpSkillBigArea->m_skillTime)
                                   {
                                       m_pRandSkill->m_iSkillState = RandSkill_State::RANDSKILL_STATE_CD;
                                       tpSkillBigArea->init();
                                       createSkillTimer();
                                       m_fCount = 0;
                                   }
    }
        break;
    case Skill::SKILL_T_FLUSH:
    {
                                 T_SkillFlush* tpSkillFlush = (T_SkillFlush*)m_pRandSkill->m_pSkill;

                                 if (m_fCount >= 1)
                                 {
                                     releasFlush();

                                     tpSkillFlush->count--;
                                     if (tpSkillFlush->count == 0)
                                     {
                                         m_pRandSkill->m_iSkillState = RandSkill_State::RANDSKILL_STATE_CD;
                                         tpSkillFlush->init();
                                         createSkillTimer();
                                     }

                                     log("Releas Flush Skill");
                                     m_fCount = 0;
                                 }

    }

        break;
    }
}


