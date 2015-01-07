#include "GameElement.h"



// void CGameElement::setCurrentAnimation(const char* arname)
// {
//     if (
//         m_pSp != nullptr &&
//         strcmp(arname, m_pSp->getAnimation()->getCurrentMovementID().c_str()) == 0
//         )
//     {
//         return;
//     }
// 
//     clearCurrentAnimation();
// 
//     m_pSp = Armature::create(arname);
//     //m_pSp->getAnimation()->setMovementEventCallFunc(this, callback);
//     addChild(m_pSp);
// }
// 
// 
// void CGameElement::clearCurrentAnimation()
// {
//     if (m_pSp != nullptr)
//     {
//         m_pSp->getAnimation()->setMovementEventCallFunc(this, nullptr);
//         m_pSp->getAnimation()->setFrameEventCallFunc(nullptr);
//         removeChild(m_pSp);
//         m_pSp = nullptr;
//     }
// }



/************************************************************************/
/*
@brief          检查随机坐标是否符合游戏逻辑标准
@param[in]      inPoint 被检测坐标
@param[out]
@return         bool
*/
/************************************************************************/
bool CGameElement::checkRandPosition(const Vec2& inPoint)
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
void CGameElement::randPosition(Vec2& outPoint)
{
    Vec2 tp;

    do
    {
        m_refShowArea->getRandVec2(tp);

    } while (!checkRandPosition(tp));


    outPoint = tp;
    //setPosition(tp);
}




/************************************************************************/
/*
@brief          当前精灵与边界碰撞检测
@param[in]
@param[out]
@return         bool 如果与边界发生碰撞返回true,否则false
*/
/************************************************************************/
bool CGameElement::collwithBorder(const Vec2& inPoint, Vec2& outPoint)
{   
    for (int i = 0; i < 4; i++)
    {
        int borderdis = m_refShowArea->getBorderDis(inPoint, CPath::DIRECT[i][0]);

        if (borderdis == -1)
        {
            continue;
        }
               
        if (borderdis <= m_iStep + m_iCollR)
        {
            outPoint = CMath::getVec2(inPoint, borderdis, CMath::angleToRadian(CPath::DIRECT[i][0]));
           // CUtil::formartGrid(outPoint);
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
bool CGameElement::collwithArea(const Vec2& inPoint, Vec2& outPoint)
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
            CUtil::formartGrid(outPoint, m_iStep);
            return true;
        }
    }
    return false;
}


void CGameElement::print(DrawNode* dn)
{
    dn->drawDot(getPosition(), m_iCollR, Color4F(1, 1, 1, 0.6));
    dn->drawDot(getPosition(), 2, Color4F(1, 0, 0, 1));
}


float CGameElement::getCollwithR()
{
    return this->m_iCollR;
}


