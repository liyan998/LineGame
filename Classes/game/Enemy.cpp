#include "GameElement.h"
                          

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
        int areaDis = m_refShowArea->getMiniAreaDis(getPosition(), CPath::DIRECT[i][0]);
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
        int borderdis = m_refSp->getPathDis(getPosition(), CPath::DIRECT[i][0]);
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