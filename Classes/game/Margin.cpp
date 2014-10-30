#include "Margin.h"
#include "framework/util/Math.h"


using namespace liyan998;

bool CMargin::init()
{    
    Sprite::init();

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


    Vec2& testEnd = CMath::getVec2(Vec2::ZERO, dis, iangle - 90);
      
    m_pDrawNode->clear();
   m_pDrawNode->drawSegment(Vec2::ZERO, Vec2(dis, 0 ), 15, Color4F(1, 1, 0, 0.5));   
}

