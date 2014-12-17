
#include "GameElement.h"
#include "util/Math.h"

#include "GameResMacros.h"


using namespace liyan998;



bool CBoss::init()
{
    Node::init();

    m_fCount    = 0.f;
    m_iDirect   = 0;
    m_iStep     = 2;
    m_iCollR = 10;
    m_iCategory = CGameElement::CATEGORY_BOSS;

    //--------------------------------------------

//     m_pSp = Sprite::create("CloseNormal.png");
//     m_pSp->setScale(1.5f); 
//     addChild(m_pSp); 

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_QINCAIDIE, 
        RES_ANIMA_PLS_QINCAIDIE, 
        RES_ANIMA_JSO_QINCAIDIE
        );

    
    m_pSp = Armature::create("Qicaidie_Walk");
    m_pSp->getAnimation()->playByIndex(1);
    m_pSp->setScale(0.5);
//     arm->getAnimation()->setSpeedScale(0.5);
    //addChild(m_pSp);

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

    CEnemy::checkWith();


//     int count = m_pArmature->getAnimation()->getMovementCount();
// 
//     std::string str = m_pArmature->getAnimation()->getCurrentMovementID();
//     log("%d  , %s" ,count, str.c_str());
  
}


void CBoss::print(DrawNode* dn)
{

    CEnemy::print(dn);

    Vec2 nps = CMath::getVec2(getPosition(), m_iStep, CMath::angleToRadian(m_iDirect));

  
    Vec2 t_oColl = getPosition();
    
    for (int i = 0; i < 4; i++)
    {

        int borderdis = m_refShowArea->getBorderDis(t_oColl, CPath::DIRECT[i][0]);

         if (borderdis == -1)
         {
             continue;
         }
        
         Vec2 endPoint = CMath::getVec2(t_oColl, borderdis, CMath::angleToRadian(CPath::DIRECT[i][0]));

        dn->drawSegment(t_oColl, endPoint, 1, Color4F(1, 1, 0, 0.3));
    }

    for (int i = 0; i < 4; i++)
    {                                                          
        int borderdis = m_refShowArea->getMiniAreaDis(t_oColl, CPath::DIRECT[i][0]);
        if (borderdis == -1)
        {
            continue;
        }
        Vec2 endPoint = CMath::getVec2(t_oColl, borderdis, CMath::angleToRadian(CPath::DIRECT[i][0]));
    
        dn->drawDot(endPoint, 10, Color4F(1, 0, 1,0.3));
    }

    for (int i = 0; i < 4; i++)
    {                                                          
        int borderdis = m_refSp->getPathDis(t_oColl, CPath::DIRECT[i][0]);
        if (borderdis == -1)
        {
            continue;
        }
        Vec2 endPoint = CMath::getVec2(t_oColl, borderdis, CMath::angleToRadian(CPath::DIRECT[i][0]));
    
        dn->drawDot(endPoint, 10, Color4F(0, 1, 1, .5));
    }                       
}      

void CBoss::setState(int state)
{
    this->m_State = state;
}

void CBoss::released()
{

}

void CBoss::animation_move()
{
 



}
