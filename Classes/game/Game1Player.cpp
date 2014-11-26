#include "Game1Player.h"
#include "util/Math.h"

using namespace liyan998;

bool CGamePlayer::init()
{
    Node::init();

    m_iStep = 6;

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
    //m_iCurrentDirect = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(getPlsyerPosition(), m_oCurrentTarget)));
    
    //log("SetTarget: %f, %f", point.x , point.y);
    if (m_State != STATE_RUN)
    {
        setState(STATE_RUN);
    }


}



int CGamePlayer::getStrackSize()
{

    return m_oAllGuide.size();
}

void CGamePlayer::addFollow(const Vec2& point)
{              

    if (m_State == STATE_RUN)
    {
        m_oAllGuide.push_back(point); 
        log("add Target point %f,%f", point.x ,point.y);
        return;
    }
    log("not target");
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

         int dis = ccpDistance(getPlsyerPosition(), m_oCurrentTarget);

         //log("target:%f,%f", m_oCurrentTarget.x, m_oCurrentTarget.y);
         if (dis < m_iStep)		 
         {               
             //log("Distance:%d", dis);
             if (m_oAllGuide.size() > 0)
             {
                 log("remove target %f, %f", m_oAllGuide[0].x, m_oAllGuide[0].y);
                 m_oAllGuide.erase(m_oAllGuide.begin());
             }
            
			 if (m_oAllGuide.size() < 1)
			 {
				 setState(STATE_STANDER);				
			 }
			 else
			 { 	 
                 setTarget(m_oAllGuide[0]);	
             }	

             return;
         }

		 m_iCurrentDirect = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(getPlsyerPosition(), m_oCurrentTarget)));
		 Vec2 npos = CMath::getVec2(getPlsyerPosition(), m_iStep, CMath::angleToRadian(m_iCurrentDirect));
		 m_pSp->setPosition(npos);  
         //log("%d, %d" ,dis, m_oAllGuide.size());
                                           
        break;
    }
}


void CGamePlayer::setState(int state)
{
    this->m_State = state;
    switch (state)
    {
    case STATE_RUN:
        //log("Player is MoveSTATE!");
        break;
    case STATE_STANDER:
        m_oAllGuide.clear();
        //log("Player is Stander");
       
        break;
    case STATE_STOP:

        m_oAllGuide.clear();
        log("Player is Stop");
        break;

    default:
        break;
    }
}