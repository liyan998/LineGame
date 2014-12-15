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
@brief          �������˵�Ŀ����߷������øñ߽�Ŀ����߷���
@param[in]      inAllPoint      ���е㼯��  
@param[out]     outAllEndPoint  ���ж˵�����߷���
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
@brief          �˵��Ͽ����߷������
@param[in]      inPoint          �˵�
@param[out]     outAllEndPoint  ���ж˵�����߷���
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
@brief          �����ڱ߽��Ͽ����߷���
@param[in]      indirect        �߽�����߷���
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
@brief          ����m_iMarginAvable�����ڱ߽��Ͽ����߷���
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
@brief          ��BOSS��ײ�߽磬�õ��ñߵ�������߷���
@param[in]
@param[out]
@return         int
*/
/************************************************************************/
int CMargin::getCollWidthRandomDirect()
{


    return m_iMarginAvable;
}