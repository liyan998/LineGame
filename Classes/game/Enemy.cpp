#include "GameElement.h"
  
#include "util/Math.h"
#include "util/Util.h"

using namespace liyan998;

/************************************************************************/
/*
@brief          当前精灵与边界碰撞检测
@param[in]
@param[out]
@return         bool 如果与边界发生碰撞返回true,否则false
*/
/************************************************************************/
bool CEnemy::collwithBorder(const Vec2& inPoint, Vec2& outPoint)
{
    for (int i = 0; i < 4; i++)
    {
        int borderdis = m_refShowArea->getBorderDis(inPoint, CPath::DIRECT[i][0]);
        if (borderdis <= m_iStep + m_iCollR)
        {

            outPoint = CMath::getVec2(inPoint, borderdis, CMath::angleToRadian(CPath::DIRECT[i][0]));
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
bool CEnemy::collwithArea(const Vec2& inPoint, Vec2& outPoint)
{
    for (int i = 0; i < 4; i++)
    {
        int areaDis = m_refShowArea->getMiniAreaDis(inPoint, CPath::DIRECT[i][0]);
        if (areaDis == -1)
        {
            continue;
        }
        if (areaDis <= m_iStep + m_iCollR)
        {                   
            outPoint = CMath::getVec2(inPoint, areaDis, CMath::angleToRadian(CPath::DIRECT[i][0]));
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
bool CEnemy::collwithGuide(const Vec2& inPoint,Vec2& outPoint)
{   
    for (int i = 0; i < 4; i++)
    {
        int borderdis = m_refSp->getPathDis(inPoint, CPath::DIRECT[i][0]);
        if (borderdis == -1)
        {
            continue;
        }

        if (borderdis <= m_iStep + m_iCollR)
        {
            outPoint = CMath::getVec2(inPoint, borderdis, CMath::angleToRadian(CPath::DIRECT[i][0]));
            return true;
        }
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

    if (collwithGuide(t_oColl, endPoint))
    {                                  
        m_refSp->setState(CMySprite::STATE_BACK);
    }
          
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

    if (collwithBorder(t_oColl, endPoint))
    {                             
        setPosition(endPoint);
        CMargin* pMargin = m_refShowArea->getBorderMargin(endPoint); 
        if (pMargin != nullptr)
        {
            m_iDirect = CUtil::getNextAngle(pMargin->m_Angle, 1) + CMath::getRandom(-80, 80);
            changeDirect(m_iDirect);
        }     

        //log("border die!!!!");
        
    }

    this->setPosition(t_oColl);

}


/************************************************************************/
/*
@brief          检查随机坐标是否符合游戏逻辑标准
@param[in]      inPoint 被检测坐标
@param[out]
@return         bool 
*/
/************************************************************************/
bool CEnemy::checkRandPosition(const Vec2& inPoint)
{

    Vec2 endPoint;
    //不能与边界碰撞
    if (collwithBorder(inPoint, endPoint))
    {                
       log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Border!");
        return false;
    }        
    //不能与解锁区域发生碰撞
    if (collwithArea(inPoint, endPoint))
    {
       log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!collwithArea!");
        return false;
    }
    return true;
}


void CEnemy::print(DrawNode* dn)
{
    dn->drawDot(getPosition(), m_iCollR, Color4F(1, 1, 1, 0.6));
    dn->drawDot(getPosition(), 2, Color4F(1, 0, 0, 1)); 
}


void CEnemy::randPosition()
{
    Vec2 tp;
   
    do
    {
        m_refShowArea->getRandVec2(tp);

    } while (!checkRandPosition(tp));

    setPosition(tp);
}


