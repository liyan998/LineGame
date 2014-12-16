#include "GameElement.h"
  
#include "util/Math.h"

using namespace liyan998;

/************************************************************************/
/*
@brief          当前精灵与边界碰撞检测
@param[in]
@param[out]
@return         bool 如果与边界发生碰撞返回true,否则false
*/
/************************************************************************/
bool CEnemy::collwithBorder(const Vec2& inPoint)
{
    for (int i = 0; i < 4; i++)
    {
        int borderdis = m_refShowArea->getBorderDis(inPoint, CPath::DIRECT[i][0]);
        if (borderdis <= m_iStep)
        {
            return true;
        }
    }
    return false;
}


/************************************************************************/
/*
@brief          当前精灵与解锁区域碰撞检测
@param[in]      inPoint 被检测坐标
@param[out]
@return         bool 如果与解锁区域相交则返回true,否则false
*/
/************************************************************************/
bool CEnemy::collwithArea(const Vec2& inPoint)
{
    for (int i = 0; i < 4; i++)
    {
        int areaDis = m_refShowArea->getMiniAreaDis(getPosition(), CPath::DIRECT[i][0]);
        if (areaDis == -1)
        {
            continue;
        }
        if (areaDis <= m_iStep)
        {                   
            return true;
        }
    }
    return false;
}

/************************************************************************/
/*
@brief          当前精灵与导线碰撞检测
@param[in]      inPoint 被检测坐标
@param[out]
@return         bool 如果与解锁区域相交则返回true,否则false
*/
/************************************************************************/
bool CEnemy::collwithGuide(const Vec2& inPoint)
{   
    for (int i = 0; i < 4; i++)
    {
        int borderdis = m_refSp->getPathDis(getPosition(), CPath::DIRECT[i][0]);
        if (borderdis == -1)
        {
            continue;
        }

        if (borderdis <= m_iStep)
        {
            return true;
        }
    }

    return false;
}


void CEnemy::checkWith()
{
    Vec2 nps = CMath::getVec2(this->getPosition(), m_iStep, CMath::angleToRadian(m_iDirect));

    if (collwithGuide(nps))
    {
        m_refSp->setState(CMySprite::STATE_BACK);
    }

    if (collwithArea(nps))
    {
        int index = m_refShowArea->getNearMargin(nps);
        if (index != SELECTID_NULL)
        {
            CMargin* margin = m_refShowArea->getAreaMargin(index);
            m_iDirect = margin->getCollWidthRandomDirect() + CMath::getRandom(-50, 50);
        }
    }

    if (collwithBorder(nps))
    {
        m_iDirect = CMath::getRandom(0, 360);
        return;
    }

    this->setPosition(nps);

}