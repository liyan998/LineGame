
#include "GameElement.h"
#include "util/Math.h"

#include "GameResMacros.h"


using namespace liyan998;

bool CBoss::init()
{
    Node::init();

    m_iCategory = CGameElement::CATEGORY_BOSS;
    
    m_fCount    = 0.f;
    m_iDirect   = 0;
    m_iStep     = 2;
    m_iCollR    = 20;
    m_iAttick   = 1;

    m_iSkillTimer   = -1;
    m_iSkillCd      = 0;

    //--------------------------------------------

//     m_pSp = Sprite::create("CloseNormal.png");
//     m_pSp->setScale(1.5f); 
//     addChild(m_pSp); 
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
            if (m_iSkillTimer-- <= 0)
            {      
                //log("skill releas!");
                m_iSkillState = RandSkill_State::RANDSKILL_STATE_RELEAS;
            }    
            m_fCount = 0;
        }
        break;
    case RANDSKILL_STATE_RELEAS:
        //log("m_iSkillCd:%f", m_fCount);
        if (m_fCount > m_iSkillCd)
        {
            createSkillTimer();
            m_fCount = 0.0f;
        }
        break;
    }        
}

void CBoss::createSkillTimer()
{
    m_iSkillTimer   = CMath::getRandom(1, 12);//
    //log("m_iSkillTimer:%d", m_iSkillTimer);
    m_iSkillCd      = 13.8;
    m_iSkillState   = RandSkill_State::RANDSKILL_STATE_WAITE;
}


float CBoss::getkillArea()
{
    if (m_iSkillState == RandSkill_State::RANDSKILL_STATE_RELEAS)
    {
        return CEnemy::getkillArea() * 5;
    }
    return CEnemy::getkillArea();
}

void CBoss::print(DrawNode* dn)
{
    if (m_iSkillState == RandSkill_State::RANDSKILL_STATE_RELEAS)
    {
        dn->drawDot(getPosition(), getkillArea(), Color4F(1, 1, 0, 0.5));
        CGameElement::print(dn);
    }
    else 
    {
        CGameElement::print(dn);
    }

//     Vec2 nps = CMath::getVec2(getPosition(), m_iStep, CMath::angleToRadian(m_iDirect));
// 
//   
//     Vec2 t_oColl = getPosition();
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

//     for (int i = 0; i < 4; i++)
//     {                                                          
//         int borderdis = m_refSp->getPathDis(t_oColl, CPath::DIRECT[i][0]);
//         if (borderdis == -1)
//         {
//             continue;
//         }
//         Vec2 endPoint = CMath::getVec2(t_oColl, borderdis, CMath::angleToRadian(CPath::DIRECT[i][0]));
//     
//         dn->drawDot(endPoint, 10, Color4F(0, 1, 1, .5));
//     }                       
}      

void CBoss::setState(int state)
{
    this->m_State = state;
}

void CBoss::released()
{

}

void CBoss::animation_move()
{
    CGameElement::setCurrentAnimation(ARMATURE_QINGCAI);
    m_pSp->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CBoss::movementCallback));
    m_pSp->getAnimation()->playByIndex(0);
}


void CBoss::changeDirect(int direct)
{

}


void CBoss::movementCallback(Armature * armature, MovementEventType type, const std::string& name)
{


}