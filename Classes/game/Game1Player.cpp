#include "Game1Player.h"
#include "util/Math.h"

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


void CGamePlayer::movePlayerTo(const Vec2& star, const Vec2& pos)
{                                  
    m_oMargin.setTaget(star, pos);

    if (m_State != STATE_RUN)
    {
        setState(STATE_RUN);
    }                              
}

void CGamePlayer::moveToPath(const std::vector<Vec2>& allPoint)
{






}


void CGamePlayer::run(float time)
{
    switch (m_State)
    {
    case STATE_RUN:


        const Vec2& currentPositon = m_pSp->getPosition();

        //log("currentPosition:%f, %f",currentPositon.x, currentPositon.y);
        int dis = ccpDistance(m_oMargin.m_oStart, m_oMargin.m_oTaget);

        int currentdis = ccpDistance(m_oMargin.m_oStart, currentPositon);

        using namespace liyan998;
        if (currentdis <= dis)
        {
            Vec2 npos = CMath::getVec2(currentPositon, m_iStep, CMath::angleToRadian(m_oMargin.m_Angle));
            m_pSp->setPosition(npos);
        } 
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