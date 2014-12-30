
#include "GameElement.h"

#include "util/Math.h"
#include "util/Util.h"

// #include "MySprite.h"
#include "GameResMacros.h"

using namespace liyan998;
using namespace cocostudio;

bool CGamePlayer::init()
{
    Node::init();

    m_iStep             = 2;
    m_iCollR            = 20;
    m_bFlow             = false;
    m_pEventAddSpeed    = nullptr;
    m_iEffectAddProtect = EFFECT_NONE;
    m_iEffectAddSpeed   = EFFECT_NONE;

    //-------------------------------------------

    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_PROPERTY_ADDSPEED, this);
    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_PROPERTY_ADDPROTECT, this);

    //-----------------------------------------------------

    setCurrentAnimation(ARMATURE_PIPI_STANDER);
    m_pSp->setAnchorPoint(Vec2(0.5f, 0.2f));
    m_pSp->getAnimation()->playByIndex(0);
    m_pSp->setOpacity(255 * .1);
                                  
    setState(STATE_STOP); 

    return true;
}

void CGamePlayer::released()
{
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_PROPERTY_ADDSPEED, this);
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_PROPERTY_ADDPROTECT, this);

    this->removeAllChildren();
}

void CGamePlayer::setPlayerPosition(const Vec2& pos)
{                      
    Vec2 tp = pos; 
    CUtil::formartGrid(tp, getStep());
    m_pSp->setPosition(tp);
}


const Vec2& CGamePlayer::getPlayerPosition()
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

    if (m_iEffectAddSpeed == Effect::EFFECT_ADDSPEED)
    {
//         float tf = m_iStep * m_pEventAddSpeed->addPart;
        step = GRAD_NUMBER(m_iStep * 3);
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

    m_iCurrentDirect = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(getPlayerPosition(), m_oCurrentTarget)));
    Vec2 npos = CMath::getVec2(getPlayerPosition(), getStep(), CMath::angleToRadian(m_iCurrentDirect));
    CUtil::formartGrid(npos, getStep());
    //CUtil::formartGrid(npos);

    m_pSp->setPosition(npos);
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

    dn->drawDot(getPlayerPosition(), getCollwithR(), Color4F(1, 0, 1, 1));
  
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
    default:
        break;
    }
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