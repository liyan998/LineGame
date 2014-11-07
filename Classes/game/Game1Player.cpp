#include "Game1Player.h"

bool CGamePlayer::init()
{                         
    Node::init();

    m_iStep = 2;

    m_pSp = Sprite::create("CloseNormal.png");   
    addChild(m_pSp);


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


void CGamePlayer::movePlayerTo(const Vec2& pos)
{        
    log("run ~~~~~~~~~~~~~~~~");
    m_pSp->runAction(MoveTo::create(m_iStep, pos));  
}

void CGamePlayer::moveToPath(const std::vector<Vec2>& allPoint)
{
    Vector< FiniteTimeAction* > allAction;

    
    for (int i = 0; i < allPoint.size();i++)
    {  
       allAction.pushBack( MoveTo::create(m_iStep, allPoint[i]) );
    }

    //allAction.pushBack(nullptr);
    //m_pSp->runAction(Sequence::create(allAction));

}