#include "Margin.h" 
#include "util/triangulate.h"
#include "util/Math.h"
#include "util/Util.h"
#include "Path.h"
#include "ShowArea.h"    


using namespace liyan998;

bool CMargin::init()
{                            
    Sprite::init();

    m_Angle             = ANGLE_NONE;
    m_iMarginAvable     = ANGLE_NONE;
    m_iAvable           = 0;

    m_pDrawNode = DrawNode::create();
    addChild(m_pDrawNode);     
   
    return true;
}
                             

void CMargin::setTaget(const Vec2& star, const Vec2& vec)
{
    m_oStart = star;
    m_oTaget = vec;

    setPosition(star); 
    onDraw();
}

                      

void CMargin::onDraw()
{   
    float dis               = ccpDistance(m_oStart, m_oTaget);
    float fRadian           = CMath::getRadian(m_oStart, m_oTaget);
    int iangle              = static_cast<int>(CMath::radianToAngle(fRadian));
    m_Angle                 = 90-iangle;
    
    //log("angle :%d", iangle);

    setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    setContentSize(Size(dis, RECTHEIGHT));
    setRotation( RA(iangle ) );


    const Vec2& testEnd = CMath::getVec2(Vec2::ZERO, dis, iangle - 90);
      

//     if (m_pDrawNode != nullptr)
//     {
//         m_pDrawNode->clear();
//         m_pDrawNode->drawSegment(Vec2::ZERO, Vec2(dis, 0), 15, Color4F(1, 1, 0, 0.5));
//     }
}
      
/************************************************************************/
/* 
@brief          设置两端点的可行走方向，设置该边界的可行走方向
@param[in]      inAllPoint      所有点集合  
@param[out]     outAllEndPoint  所有端点可行走方向
@return         void                                           
*/
/************************************************************************/
void CMargin::getAvableDirect
(
    const std::vector<Vec2>&        inAllPoint,
    std::map<Vec2, unsigned int>&   outAllEndPoint
)
{  
    addPointToMap(m_oStart, outAllEndPoint);
    addPointToMap(m_oTaget, outAllEndPoint); 
}

/************************************************************************/
/*
@brief          端点上可行走方向添加
@param[in]      inPoint          端点
@param[out]     outAllEndPoint  所有端点可行走方向
@return         void
*/
/************************************************************************/
void CMargin::addPointToMap(const Vec2& inPoint,std::map<Vec2, unsigned int>& outAllEndPoint)
{                                                        
    CShowArea::EndPointIterator endpIter = outAllEndPoint.find(inPoint);
    unsigned int amargin = CUtil::converDirectToFlag(m_iMarginAvable);

    if (endpIter != outAllEndPoint.end())
    {
        endpIter->second |= amargin;       
    }
    else
    {              
        outAllEndPoint.insert(CShowArea::EndPointPair(inPoint, amargin));   
    }
}

/************************************************************************/
/* 
@brief          设置在边界上可行走方向
@param[in]      indirect        边界可行走方向
@param[out]     
@return         void
*/
/************************************************************************/
void CMargin::setAvableDirect(int direct)
{
    this->m_iMarginAvable = direct;


    setAvableDirect();
}



/************************************************************************/
/* 
@brief          根据m_iMarginAvable设置在边界上可行走方向
@param[in]      
@param[out]
@return         void

*/
/************************************************************************/
void CMargin::setAvableDirect()
{
    m_iAvable |= CUtil::converDirectToFlag(m_iMarginAvable);
    m_iAvable |= CUtil::converDirectToFlag(m_Angle);
    m_iAvable |= CUtil::converDirectToFlag(CUtil::getRevceDircet(m_Angle));

    //log("%x", m_iAvable);
}



/************************************************************************/
/*
@brief          当BOSS碰撞边界，得到该边的随机行走方向
@param[in]
@param[out]
@return         int
*/
/************************************************************************/
int CMargin::getCollWidthRandomDirect()
{


    return m_iMarginAvable;
}