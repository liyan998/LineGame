#include "GameElement.h"
  
#include "util/Math.h"
#include "util/Util.h"

using namespace liyan998;



int CEnemy::getAttack()
{
    return this->m_iAttick;
}

/************************************************************************/
/*
@brief          当前精灵与导线碰撞检测
@param[in]      inPoint 被检测坐标
@param[out]
@return         bool 如果与解锁区域相交则返回true,否则false
*/
/************************************************************************/
bool CEnemy::collwithGuide(const Vec2& inPoint,Vec2& outPoint)
{   
    for (int i = 0; i < 4; i++)
    {
        int borderdis = m_refSp->getPathDis(inPoint, CPath::DIRECT[i][0]);
        if (borderdis == -1)
        {
            continue;
        }

        if (borderdis <= m_iStep + getCollwithR())
        {
            outPoint = CMath::getVec2(inPoint, borderdis, CMath::angleToRadian(CPath::DIRECT[i][0]));
            
            return true;
        }
    }
    return false;
}

/************************************************************************/
/* 
@brief          当前精灵与玩家碰撞检测
@param[in]      inPoint 被检测坐标
@param[out]
@return         bool 是否发生碰撞

*/
/************************************************************************/
bool CEnemy::collwithPlayer(const Vec2& inPoint)
{
    int distanc = ccpDistance(inPoint, m_refPlayer->getPlayerPosition());
    int collr = getCollwithR() + m_refPlayer->getCollwithR();
    if (distanc <= collr)
    {
        return true;
    }

    return false;
}


/************************************************************************/
/*
@brief          检查各种碰撞
@param[in]    
@param[out]
@return         void
*/
/************************************************************************/
void CEnemy::checkWith()
{
    Vec2 t_oColl = CMath::getVec2(this->getPosition(), m_iStep, CMath::angleToRadian(m_iDirect));
    Vec2 endPoint;

    //---------------------------------------------------

    switch (m_refSp->getState())
    {
    case CMySprite::STATE_DRAW:
    case CMySprite::STATE_CLOSE:

        if (
            //collwithPlayer(t_oColl) || 
            collwithGuide(t_oColl, endPoint) )
        {                   
            m_refSp->attiack(getAttack(),this);
            return;
        }

        break;
    default:
        break;
    }

    //----------------------------------------------

    if (collwithArea(t_oColl, endPoint))
    {            
        int index = m_refShowArea->getNearMargin(endPoint);
        if (index != SELECTID_NULL)
        {                
            CMargin* margin = m_refShowArea->getAreaMargin(index);
            m_iDirect = margin->getCollWidthRandomDirect() + CMath::getRandom(-50, 50);
            changeDirect(m_iDirect);           
        }
    }   

    //---------------------------------------------------

    if (collwithBorder(t_oColl, endPoint))
    {     
       setPosition(endPoint);
 
        CMargin* pMargin = m_refShowArea->getBorderMargin(endPoint); 
        if (pMargin != nullptr)
        {            
            m_iDirect = CUtil::getNextAngle(pMargin->m_Angle, 1) + CMath::getRandom(-80, 80);
            changeDirect(m_iDirect);    
        }     
    }

    //---------------------------------------------------

    this->setPosition(t_oColl);
}


