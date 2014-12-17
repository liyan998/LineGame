#include "GameElement.h"
  
#include "util/Math.h"

using namespace liyan998;

/************************************************************************/
/*
@brief          ��ǰ������߽���ײ���
@param[in]
@param[out]
@return         bool �����߽緢����ײ����true,����false
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
@brief          ��ǰ���������������ײ���
@param[in]      inPoint ���������
@param[out]
@return         bool �������������ཻ�򷵻�true,����false
*/
/************************************************************************/
bool CEnemy::collwithArea(const Vec2& inPoint)
{
    for (int i = 0; i < 4; i++)
    {
        int areaDis = m_refShowArea->getMiniAreaDis(inPoint, CPath::DIRECT[i][0]);
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
@brief          ��ǰ�����뵼����ײ���
@param[in]      inPoint ���������
@param[out]
@return         bool �������������ཻ�򷵻�true,����false
*/
/************************************************************************/
bool CEnemy::collwithGuide(const Vec2& inPoint)
{   
    for (int i = 0; i < 4; i++)
    {
        int borderdis = m_refSp->getPathDis(inPoint, CPath::DIRECT[i][0]);
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

    m_iCollR = 10;
    Vec2 t_oColl = CMath::getVec2(nps, m_iCollR, CMath::angleToRadian(m_iDirect));

    if (collwithGuide(t_oColl))
    {
        m_refSp->setState(CMySprite::STATE_BACK);
    }

    if (collwithArea(t_oColl))
    {
        int index = m_refShowArea->getNearMargin(t_oColl);
        if (index != SELECTID_NULL)
        {
            CMargin* margin = m_refShowArea->getAreaMargin(index);
            m_iDirect = margin->getCollWidthRandomDirect() + CMath::getRandom(-50, 50);
        }
    }

    if (collwithBorder(t_oColl))
    {
        m_iDirect = CMath::getRandom(0, 360);
        return;
    }

    this->setPosition(nps);

}