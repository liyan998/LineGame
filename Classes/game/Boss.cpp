
#include "GameElement.h"
#include "util/Math.h"

#include "GameResMacros.h"


using namespace liyan998;

bool CBoss::init()
{
    Node::init();

    m_iCategory     = CGameElement::CATEGORY_BOSS;
    m_iSkillState   = RandSkill_State::RANDSKILL_STATE_NONE;
    
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
   
    //创建随机技能
    createSkillTimer();

    animation_move();
}

void CBoss::run(float t)
{                    
    m_fCount += t;
    
    randSkillTimer();  
   
   //---------------------------- 

    if (m_iSkillState == RANDSKILL_STATE_RELEAS 
        &&
        m_pRandSkill->m_iSkillId == Skill::SKILL_T_BIGAREA)
    {

        Vec2 tP;
        switch (m_refSp->getState())
        {
        case CMySprite::STATE_DRAW:
        case CMySprite::STATE_CLOSE:

            if (collwithPlayer(getPosition()) || collwithGuide(getPosition(), tP))
            {
                m_refSp->attiack(getAttack(), this);
                return;
            }

            break;
        default:
            break;
        }
        return;
    }

    CEnemy::checkWith();  
}

void CBoss::randSkillTimer()
{
    switch (m_iSkillState)
    {
    case RANDSKILL_STATE_WAITE:
        if (m_fCount > 1.0f)
        {
            //log("m_iSkillTim1er:%d", m_iSkillTimer);
            if (m_pRandSkill->m_iSkillTimer-- <= 0)
            {      
                //log("skill releas!");
                m_iSkillState = RandSkill_State::RANDSKILL_STATE_RELEAS;
            }    
            m_fCount = 0;
        }
        break;
    case RANDSKILL_STATE_RELEAS:
        //log("m_iSkillCd:%f", m_fCount);
        if (m_fCount > m_pRandSkill->m_iSkillCd)
        {
            createSkillTimer();
            m_fCount = 0.0f;
        }
        break;
    }        
}

void CBoss::createSkillTimer()
{
    m_iSkillState   = RandSkill_State::RANDSKILL_STATE_WAITE;

    if (m_pRandSkill != nullptr)
    {
        delete m_pRandSkill;
        m_pRandSkill = nullptr;
    }


    m_pRandSkill = new T_RandSkill();
    m_pRandSkill->m_iSkillTimer     = CMath::getRandom(1, 12);// 
    m_pRandSkill->m_iSkillCd        = 13.8;
    m_pRandSkill->m_iSkillId        = Skill::SKILL_T_BIGAREA;
}


float CBoss::getCollwithR()
{
    if (m_iSkillState == RandSkill_State::RANDSKILL_STATE_RELEAS)
    {
        return CEnemy::getCollwithR() * 5;
    }
    return CEnemy::getCollwithR();
}

void CBoss::print(DrawNode* dn)
{
    if (m_iSkillState == RandSkill_State::RANDSKILL_STATE_RELEAS)
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
    if (m_pRandSkill != nullptr)
    {
        delete m_pRandSkill;
        m_pRandSkill = nullptr;
    }
}

void CBoss::animation_move()
{
    CGameElement::setCurrentAnimation(ARMATURE_QINGCAI);
    m_pArmature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CBoss::movementCallback));
    m_pArmature->getAnimation()->playByIndex(0);
}


void CBoss::changeDirect(int direct)
{

}


void CBoss::movementCallback(Armature * armature, MovementEventType type, const std::string& name)
{


}