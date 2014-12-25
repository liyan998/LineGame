#include "GameElement.h"
  
#include "util/Math.h"
#include "util/Util.h"

#include "EventSystem.h"

using namespace liyan998;


inline
int CEnemy::getAttack()
{
    return this->m_iAttick;
}

/************************************************************************/
/*
@brief          ��ǰ�����뵼����ײ���
@param[in]      inPoint ���������
@param[out]
@return         bool �������������ཻ�򷵻�true,����false
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
            CUtil::formartGrid(outPoint, m_iStep);
            return true;
        }
    }

    return false;
}


/************************************************************************/
/*
@brief          ��������ײ
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
        m_refSp->attiack(getAttack());
//         if (!)
//         {
//             
//         }
        return;
    }
            
    if (collwithArea(t_oColl, endPoint))
    {            
        int index = m_refShowArea->getNearMargin(endPoint);
        if (index != SELECTID_NULL)
        {                
            CMargin* margin = m_refShowArea->getAreaMargin(index);
            m_iDirect = margin->getCollWidthRandomDirect() + CMath::getRandom(-50, 50);
            changeDirect(m_iDirect);
            //return;
            //t_oColl = CMath::getVec2(this->getPosition(), m_iStep, CMath::angleToRadian(m_iDirect));
        }
    }
   
    if (collwithBorder(t_oColl, endPoint))
    {                             
       setPosition(endPoint);
       //log("1>>>"); 
        CMargin* pMargin = m_refShowArea->getBorderMargin(endPoint); 
        if (pMargin != nullptr)
        {
           // log("2<<<");
            m_iDirect = CUtil::getNextAngle(pMargin->m_Angle, 1) + CMath::getRandom(-80, 80);
            changeDirect(m_iDirect);
            //return;
            //t_oColl = CMath::getVec2(this->getPosition(), m_iStep, CMath::angleToRadian(m_iDirect));
        
//             setPosition(t_oColl);
//return;
        }     

    }

    this->setPosition(t_oColl);

}





// void CEnemy::print(DrawNode* dn)
// {
//     dn->drawDot(getPosition(), m_iCollR, Color4F(1, 1, 1, 0.6));
//     dn->drawDot(getPosition(), 2, Color4F(1, 0, 0, 1)); 
// }


