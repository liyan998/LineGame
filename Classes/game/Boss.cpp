
#include "GameElement.h"
#include "util/Math.h"

using namespace liyan998;


bool CBoss::init()
{
    Node::init();

    m_fCount    = 0.f;
    m_iDirect   = 0;
    m_iStep     = 1;

    //--------------------------------------------

    m_pSp = Sprite::create("CloseNormal.png");
    m_pSp->setScale(1.5f); 
    addChild(m_pSp); 

    return true;
}

void CBoss::run(float t)
{                    
//    (m_fCount += t);
// 
//    if (m_fCount > 1.0f)
//    {                
//        m_fCount = 0;
//    } 
   //---------------------------- 

   Vec2 nps = CMath::getVec2(this->getPosition(), m_iStep, CMath::angleToRadian(m_iDirect));


   if (collwithGuide(nps))
   {
       m_refSp->setState(CMySprite::STATE_BACK);
       //m_refSp->clearGuide();
   }
   
   if (collwithArea(nps))
   {
       int index = m_refShowArea->getNearMargin(nps);
       if (index != SELECTID_NULL)
       {
           CMargin* margin = m_refShowArea->getAreaMargin(index);
           m_iDirect = margin->getCollWidthRandomDirect() + CMath::getRandom(-50 , 50);
       }

   }

   if (collwithBorder(nps))
   {
       m_iDirect = CMath::getRandom(0, 360);
       return;
   }                

   this->setPosition(nps);
}


void CBoss::print(DrawNode* dn)
{
    dn->drawDot(getPosition(), 20, Color4F(1, 1, 1, 0.6));
    for (int i = 0; i < 4; i++)
    {

        int borderdis = m_refShowArea->getBorderDis(getPosition(), CPath::DIRECT[i][0]);
    
         if (borderdis == -1)
         {
             continue;
         }
        
        Vec2 endPoint = CMath::getVec2(getPosition(), borderdis, CMath::angleToRadian(CPath::DIRECT[i][0]));

        dn->drawSegment(getPosition(), endPoint, 1, Color4F(1, 1, 0, 0.3));
    }

    for (int i = 0; i < 4; i++)
    {                                                          
        int borderdis = m_refShowArea->getMiniAreaDis(getPosition(), CPath::DIRECT[i][0]);
        if (borderdis == -1)
        {
            continue;
        }
        Vec2 endPoint = CMath::getVec2(getPosition(), borderdis, CMath::angleToRadian(CPath::DIRECT[i][0]));
    
        dn->drawDot(endPoint, 10, Color4F(1, 0, 1,0.3));
    }

    for (int i = 0; i < 4; i++)
    {                                                          
        int borderdis = m_refSp->getPathDis(getPosition(), CPath::DIRECT[i][0]);       
        if (borderdis == -1)
        {
            continue;
        }
        Vec2 endPoint = CMath::getVec2(getPosition(), borderdis, CMath::angleToRadian(CPath::DIRECT[i][0]));
    
        dn->drawDot(endPoint, 10, Color4F(0, 1, 1, .5));
    }


}


void CBoss::animation_move()
{
 



}
