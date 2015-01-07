
#include "GameElement.h"
#include "util/Math.h"

#include "GameResMacros.h"


using namespace liyan998;

bool CBoss::init()
{
    Node::init();

    m_iCategory         = CGameElement::CATEGORY_BOSS;
    m_iRandSkillState   = RandSkill_State::RANDSKILL_STATE_CD;
    
    m_fCount        = 0.f;
    m_iDirect       = 0;
    m_iStep         = 2;
    m_iCollR        = 20;
    m_iAttick       = 1;

    return true;
}


void CBoss::onEnter()
{
    Node::onEnter();

//     T_SkillBigArea* tPBigArea   = new T_SkillBigArea();
//     tPBigArea->m_fArea          = 3.0f; //面积扩展倍数
//     tPBigArea->m_fMaxTime       = 10;   //持续时间
// 
//     T_SkillFlush* tPFlush       = new T_SkillFlush();
//     tPFlush->m_iMaxCount        = 3;
// 
//     //技能的初始化
//     T_RandSkill allskill[] = 
//     {
//         { 20,0, Skill::SKILL_T_BIGAREA,   RANDSKILL_STATE_CD, static_cast<T_SkillData*>(tPBigArea) },
//         { 15,0,Skill::SKILL_T_FLUSH,     RANDSKILL_STATE_CD, static_cast<T_SkillData*>(tPFlush) }
//     };    
//     
//     for (int i = 0; i < 2;i++)
//     {
//         T_RandSkill* t_pRskill = new T_RandSkill();
// 
//         t_pRskill->m_iMaxCD         = allskill[i].m_iMaxCD;
//         t_pRskill->m_iSkillId       = allskill[i].m_iSkillId;
//         t_pRskill->m_iSkillState    = allskill[i].m_iSkillState;
//         t_pRskill->m_pSkill         = allskill[i].m_pSkill;
//         t_pRskill->init();
// 
//         m_oAllRandSkill.push_back(t_pRskill);
//     }
   
    //--------------------------------------------------------------


    //创建随机技能
    //createSkillTimer();

    //animation_move();
}

void CBoss::run(float t)
{                    
    m_fCount += t;
    m_fSkillCdCount += t;
    
    skillCd();
    
    randSkillTimer();  
   
   //---------------------------- 

    if (hasKeepMoveing())
    {
        CEnemy::checkWith();  
    }
}
// 
bool CBoss::hasKeepMoveing()
{    
    return true;
}

void CBoss::randSkillTimer()
{
    switch (m_iRandSkillState)
    {
    case RANDSKILL_STATE_READY:
        if (m_fCount > 1.0f)
        {
            //log("m_iSkillTim1er:%d", m_iSkillTimer);
            if (m_iSkillTimer-- <= 1)
            {                      
                randSkillCreate();
                m_iRandSkillState = RandSkill_State::RANDSKILL_STATE_RELEAS;
            }    
            m_fCount = 0;
        }
        break;
    case RANDSKILL_STATE_RELEAS:
        randSkillRelease();
        break;
    }        
}

void CBoss::createSkillTimer()
{
    m_iRandSkillState  = RandSkill_State::RANDSKILL_STATE_READY;
    m_iSkillTimer     = CMath::getRandom(15, 35);// 
}


void CBoss::randSkillCreate()
{
    m_pRandSkill = nullptr;

    std::vector<int> t_oAllIndex;

    for (int i = 0; i < m_oAllRandSkill.size();i++)
    {
        if (m_oAllRandSkill[i]->m_iSkillState == RandSkill_State::RANDSKILL_STATE_READY)
        {
            t_oAllIndex.push_back(i);
        }        
    }

    int index = CMath::getRandom(0, t_oAllIndex.size() - 1);
    m_pRandSkill = m_oAllRandSkill[index];
    m_pRandSkill->init();

    log("Create Skill:%d", m_pRandSkill->m_iSkillId);

   
}

void CBoss::randSkillRelease()
{
    //log("m_iSkillCd:%f", m_fCount); 
 
}



void CBoss::skillCd()
{
    if (m_fSkillCdCount >= 1.f)
    {
        //log("---------------------");
        for (int i = 0; i < m_oAllRandSkill.size();i++)
        {
            if (m_oAllRandSkill[i]->m_iSkillState == RandSkill_State::RANDSKILL_STATE_CD)
            {
                m_oAllRandSkill[i]->m_iSkillCd--;
                if (m_oAllRandSkill[i]->m_iSkillCd <= 0)
                {
                    m_oAllRandSkill[i]->m_iSkillState = RandSkill_State::RANDSKILL_STATE_READY;
                }
            }
            //log("%d m_oAllRandSkill[i]->m_iSkillCd:%d", m_oAllRandSkill[i]->m_iSkillState, m_oAllRandSkill[i]->m_iSkillCd);
        }
        m_fSkillCdCount = 0.0f;
    }
}


float CBoss::getCollwithR()
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

void CBoss::print(DrawNode* dn)
{
    if (m_iRandSkillState == RandSkill_State::RANDSKILL_STATE_RELEAS)
    {
        dn->drawDot(getPosition(), getCollwithR(), Color4F(1, 1, 0, 0.5));       
    }
    
    CGameElement::print(dn);
    

//     Vec2 nps = CMath::getVec2(getPosition(), m_iStep, CMath::angleToRadian(m_iDirect));
// 
//   
     Vec2 t_oColl = getPosition();
//     
//     for (int i = 0; i < 4; i++)
//     {
// 
//         int borderdis = m_refShowArea->getBorderDis(t_oColl, CPath::DIRECT[i][0]) - m_iCollR;
// 
//          if (borderdis == -1)
//          {
//              continue;
//          }
//         
//          Vec2 endPoint = CMath::getVec2(t_oColl, borderdis, CMath::angleToRadian(CPath::DIRECT[i][0]));
// 
//         dn->drawSegment(t_oColl, endPoint, 1, Color4F(1, 1, 0, 0.3));
//         dn->drawDot(endPoint, 10, Color4F(1, 0, 1, 0.3));
//     }

//     for (int i = 0; i < 4; i++)
//     {                                                          
//         int borderdis = m_refShowArea->getMiniAreaDis(t_oColl, CPath::DIRECT[i][0]);
//         if (borderdis == -1)
//         {
//             continue;
//         }
//         Vec2 endPoint = CMath::getVec2(t_oColl, borderdis, CMath::angleToRadian(CPath::DIRECT[i][0]));
//     
//         dn->drawDot(endPoint, 10, Color4F(1, 0, 1,0.3));
//     }

    for (int i = 0; i < 4; i++)
    {                                                          
        int borderdis = m_refSp->getPathDis(t_oColl, CPath::DIRECT[i][0]);
        if (borderdis == -1)
        {
            continue;
        }
        Vec2 endPoint = CMath::getVec2(t_oColl, borderdis, CMath::angleToRadian(CPath::DIRECT[i][0]));
    
        dn->drawDot(endPoint, 10, Color4F(0, 1, 1, .5));
    }                       
}      

void CBoss::setState(int state)
{
    this->m_State = state;
}

void CBoss::released()
{

}

// void CBoss::animation_move()
// {
//     CGameElement::setCurrentAnimation(ARMATURE_QINGCAI);
//     m_pArmature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CBoss::movementCallback));
//     m_pArmature->getAnimation()->playByIndex(0);
// }


void CBoss::changeDirect(int direct)
{

}


void CBoss::movementCallback(Armature * armature, MovementEventType type, const std::string& name)
{


}