#include "Player.h"

bool CPlayer::init()
{                         
    Node::init();

    m_iStep = 2;

    m_pSp = Sprite::create("CloseNormal.png");   
    addChild(m_pSp);


    return true;
}


void CPlayer::setPlayerPosition(const Vec2& pos)
{

    m_pSp->setPosition(pos);
}


const Vec2& CPlayer::getPlsyerPosition()
{                                     
    return m_pSp->getPosition();
}


void CPlayer::movePlayerTo(const Vec2& pos)
{        
    log("run ~~~~~~~~~~~~~~~~");
    m_pSp->runAction(MoveTo::create(m_iStep, pos));  
}

void CPlayer::moveToPath(const std::vector<Vec2>& allPoint)
{
    Vector< FiniteTimeAction* > allAction;

    
    for (int i = 0; i < allPoint.size();i++)
    {  
       allAction.pushBack( MoveTo::create(m_iStep, allPoint[i]) );
    }

    //allAction.pushBack(nullptr);
    m_pSp->runAction(Sequence::create(allAction));

}