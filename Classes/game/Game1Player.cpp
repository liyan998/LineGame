
#include "Game1Player.h"

#include "util/Math.h"
#include "util/Util.h"

// #include "MySprite.h"
#include "GameResMacros.h"

using namespace liyan998;
using namespace cocostudio;

bool CGamePlayer::init()
{
    Node::init();

    m_iStep     = 2;
    m_bFlow     = false;
    m_iPower    = 3;

//     m_pSp = Sprite::create("CloseNormal.png");
//     addChild(m_pSp);

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_PIPI,
        RES_ANIMA_PLS_PIPI,
        RES_ANIMA_JSO_PIPI
        );


    setCurrentAnimation(ARMATURE_PIPI_STANDER);

    m_pSp->setAnchorPoint(Vec2(0.5f, 0.2f));
    m_pSp->getAnimation()->playByIndex(0);

   //m_pSp->setPosition(Vec2(0, 30));

                              
    setState(STATE_STOP); 
    //schedule(schedule_selector(CGamePlayer::run));

    return true;
}

void CGamePlayer::released()
{
    this->removeAllChildren();
}

void CGamePlayer::setPlayerPosition(const Vec2& pos)
{                      
    Vec2 tp = pos; 
    CUtil::formartGrid(tp, m_iStep);
    m_pSp->setPosition(tp);
}


const Vec2& CGamePlayer::getPlsyerPosition()
{
    return m_pSp->getPosition();
}


void CGamePlayer::setTarget(const Vec2& point)
{  
    m_oCurrentTarget = point; 
    //m_iCurrentDirect = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(getPlsyerPosition(), m_oCurrentTarget)));
    
    //log("SetTarget: %f, %f", point.x , point.y);
    if (m_State != STATE_RUN)
    {
        setState(STATE_RUN);
    }
}


void CGamePlayer::checkPosition(const Vec2& inPoint)
{      
    if (m_State == STATE_STOP && getPlsyerPosition() != inPoint)
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
    return this->m_iStep;
}

void CGamePlayer::run(float time)
{
    //log("-------------------------------");
	//log("plyer urn %d ,%d", m_State ,m_oAllGuide.size());
    switch (m_State)
    {
    case STATE_RUN:
    {
         int dis = ccpDistance(getPlsyerPosition(), m_oCurrentTarget);

         //log("%d  target:%f,%f", dis, m_oCurrentTarget.x, m_oCurrentTarget.y);
         if (dis < m_iStep)		 
         {               
             setState(STATE_STANDER);
             return;
         }
         
		 m_iCurrentDirect = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(getPlsyerPosition(), m_oCurrentTarget)));
		 Vec2 npos = CMath::getVec2(getPlsyerPosition(), m_iStep, CMath::angleToRadian(m_iCurrentDirect));
         CUtil::formartGrid(npos, m_iStep);

         m_pSp->setPosition(npos);
    }
                                           
        break;
    case STATE_STANDER:
    {                                    
        if (m_oAllGuide.size() < 1)
        {
            setState(STATE_STOP);
            break;
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
            break;
        }
        setTarget(m_oAllGuide[0]);
    }
        break;
    case STATE_STOP:
    
        if (m_oAllGuide.size() > 0)
        {
            setTarget(m_oAllGuide[0]);
        }
    
        break;
    }
}


void CGamePlayer::print(DrawNode* dn)
{

}

void CGamePlayer::setState(int state)
{
    this->m_State = state;
    switch (state)
    {
    case STATE_RUN:
        log("Player is MoveSTATE!");
        break;
    case STATE_STANDER:
        //m_oAllGuide.clear();
        log("Player is Stander");       
        break;
    case STATE_STOP:   
        m_oAllGuide.clear();
        log("Player is Stop");
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

//TODO 完成动画
void CGamePlayer::animation_idle()
{

}

//TODO 完成动画
void CGamePlayer::animation_attack()
{

}

//TODO 完成动画
void CGamePlayer::animation_die()
{

}

//TODO 完成动画
void CGamePlayer::animation_move()
{

}