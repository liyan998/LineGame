#include "Margin.h" 
#include "util/triangulate.h"
#include "util/Math.h"
#include "util/Util.h"
#include "Path.h"



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


    const Vec2& testEnd = CMath::getVec2(Vec2::ZERO, dis, iangle - 90);
      

//     if (m_pDrawNode != nullptr)
//     {
//         m_pDrawNode->clear();
//         m_pDrawNode->drawSegment(Vec2::ZERO, Vec2(dis, 0), 15, Color4F(1, 1, 0, 0.5));
//     }
}




//�õ����������� allpoint area
//���ض˵�
unsigned int CMargin::getAvableDirect(const std::vector<Vec2>& allPoint)
{
    //�������
    unsigned int dis = ccpDistance(m_oStart, m_oTaget);
    //�е�����
    Vec2 mp = CMath::getVec2(m_oStart, dis / 2, (CMath::angleToRadian(m_Angle)));
    CMath::getIntPoint(mp);
   
    //�˵�

    //

//     for (int i = 0; i < MAXDIRECT;i++)
//     {
//         int checkdirect = CPath::DIRECT[i][0];
// 
//         Vec2 dp = CMath::getVec2(mp, GRAD_CELL * 2, (CMath::angleToRadian(checkdirect)));
//         CMath::getIntPoint(dp);

//         if (checkdirect == m_Angle || CUtil::hasRevceDircet(checkdirect))
//         {
//         }

//         if (CUtil::hasPointInPloyon(allPoint, dp))
//         {
//             log("inPloyon!!!!");
//         }
        
        
       // log("direct:%d , %f, %f", CPath::DIRECT[i][0], dp.x, dp.y);

    //}


    return 0;
}