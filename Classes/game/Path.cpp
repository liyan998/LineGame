#include "Path.h"   
#include "util/Math.h"
#include "util/Util.h"
#include "Margin.h"

int CPath::DIRECT[MAXDIRECT][DIRECT_SELECT] =
{
    //angle ,逆时针，   顺时针
    { 90,   180,    0 },
    { 0,    90,     -90 },
    { -90,  0,      180 },
    { 180,  -90,    90 }
};





using namespace liyan998;

void CPath::print( DrawNode* dn)
{
	for (int i = 0; i < m_oAllPoint.size(); i++)
	{
		if (i + 1 < m_oAllPoint.size())
		{
			dn->drawSegment(m_oAllPoint[i], m_oAllPoint[i + 1], 2, Color4F(0, .5F, .5F, .5F));
		}       
	}
    float rC = liyan998::CMath::getRandom(1, 100) / 100.f;
    float gC = liyan998::CMath::getRandom(1, 100) / 100.f;
    float bC = liyan998::CMath::getRandom(1, 100) / 100.f;


	for (int i = 0 ;i < m_oAllPoint.size();i++)
    {
        dn->drawDot(m_oAllPoint[i], 4, Color4F(1, 0, 0, 1));
        dn->drawDot(m_oAllPoint[i], 3, Color4F(rC, gC, bC, 1));        
	}
}

void CPath::clearPoint()
{        
	m_oAllPoint.clear();
}





/*********************************************************************/
/**
* @brief        得到当前位置 与PATH 关联的可行走方向
* @param[in]    currentDirect 当前方向
                inPoint       当前位置
* @param[out]   outDirect     方向集合 
* @return       void
*/
/*********************************************************************/
void CPath::getMoveAble(int currentDirect, const Vec2& inPoint, std::vector<int>& outDirect)
{ 
    if (m_oAllPoint.size() > 3)
    {               
        //const Vec2& vD1         = *(m_oAllPoint.end() - 2);
        //const Vec2& vD2         = *(m_oAllPoint.end() - 1);
        //int pathCurrentDirect   = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(vD1, vD2)));      
        //outDirect.push_back(CUtil::getRevceDircet(pathCurrentDirect));
        //log("%d~~~~~~~%f, %f", pathCurrentDirect, inPoint.x, inPoint.y);

        Vec2 nextStep = CMath::getVec2(inPoint, GRAD_CELL, CMath::angleToRadian(currentDirect));
        CUtil::formartGrid(nextStep);

        log("currentDirect:%d, nextStep:%f,%f", currentDirect, nextStep.x, nextStep.y);





        if (!hasPointInLine(nextStep))
        {
            outDirect.push_back(currentDirect);
        }    

        return;
    }


    
    outDirect.push_back(ANGLE_LEFT);
    outDirect.push_back(ANGLE_RIGHT);
    outDirect.push_back(ANGLE_DOWN);
    outDirect.push_back(ANGLE_UP);
}


bool CPath::hasPointInLine(const Vec2& inPoint)
{

//     if (CUtil::hasPointInLine())
//     {
//     }

    if (inPoint == *(m_oAllPoint.end() - 1))
    {
        return false;
    }

    for (int i = 0; i < m_oAllPoint.size() - 1;i++)
    {


            if (CUtil::hasPointInLine(m_oAllPoint[i] ,m_oAllPoint[i + 1], inPoint))
            {
                return true;
            }
        //}
    }

    return false;
}