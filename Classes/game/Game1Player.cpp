#include "Game1Player.h"
#include "util/Math.h"

using namespace liyan998;

bool CGamePlayer::init()
{
    Node::init();

    m_iStep = 2;

    m_pSp = Sprite::create("CloseNormal.png");
    addChild(m_pSp);
                              
    setState(STATE_STOP); 
    schedule(schedule_selector(CGamePlayer::run));

    return true;
}


void CGamePlayer::setPlayerPosition(const Vec2& pos)
{                               
    m_pSp->setPosition(pos);
}


const Vec2& CGamePlayer::getPlsyerPosition()
{
    return m_pSp->getPosition();
}


void CGamePlayer::setTarget(const Vec2& point)
{  
    m_oCurrentTarget = point; 
    m_iCurrentDirect = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(getPlsyerPosition(), m_oCurrentTarget)));
    setState(STATE_RUN);
}



int CGamePlayer::getStrackSize()
{

    return m_oAllGuide.size();
}

void CGamePlayer::addFollow(const Vec2& point)
{              
    m_oAllGuide.push_back(point); 
}


void CGamePlayer::movePlayerTo(const Vec2& star, const Vec2& pos)
{                                  
                         
}

void CGamePlayer::moveToPath(const std::vector<Vec2>& allPoint)
{






}


void CGamePlayer::run(float time)
{
    switch (m_State)
    {
    case STATE_RUN:     
                            

         int dis = ccpDistance(getPlsyerPosition(), m_oCurrentTarget);
         if (dis > m_iStep)
         {      
             m_iCurrentDirect = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(getPlsyerPosition(), m_oCurrentTarget)));
             Vec2 npos = CMath::getVec2(getPlsyerPosition(), m_iStep, CMath::angleToRadian(m_iCurrentDirect));
             m_pSp->setPosition(npos);               
         }
         else if (m_oAllGuide.size() > 0)
         {
             m_oCurrentTarget = m_oAllGuide[0];
             m_oAllGuide.erase(m_oAllGuide.begin());
            
         }
         else
         {
             setState(STATE_STANDER);
         }

         log("%d, %d" ,dis, m_oAllGuide.size());
                                           
        break;
    }
}


void CGamePlayer::setState(int state)
{
    this->m_State = state;
    switch (state)
    {
    case STATE_RUN:
        log("Player is MoveSTATE!");
        break;
    default:
        break;
    }
}