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
// 	for (int i = 0; i < m_oAllPoint.size(); i++)
// 	{
// 		if (i + 1 < m_oAllPoint.size())
// 		{
// 			dn->drawSegment(m_oAllPoint[i], m_oAllPoint[i + 1], 2, Color4F(0, .5F, .5F, .5F));
// 		}       
// 	}
//     float rC = liyan998::CMath::getRandom(1, 100) / 100.f;
//     float gC = liyan998::CMath::getRandom(1, 100) / 100.f;
//     float bC = liyan998::CMath::getRandom(1, 100) / 100.f;


// 	for (int i = 0 ;i < m_oAllPoint.size();i++)
//     {
//         dn->drawDot(m_oAllPoint[i], 4, Color4F(1, 0, 0, 1));
//         dn->drawDot(m_oAllPoint[i], 3, Color4F(rC, gC, bC, 1));        
// 	}
}

void CPath::clearPoint()
{        
	m_oAllPoint.clear();
}


void CPath::addPoint(const Vec2& inPoint)
{
    m_oAllPoint.push_back(inPoint);
}

/************************************************************************/
/*



*/
/************************************************************************/
bool CPath::hasOverLoad(const Vec2& inSP, Vec2& inCP, int angle)
{

    //log("CPath hasOverLoad:%f, %f, %d", inSP.x, inSP.y, angle);
    Size visSize = Director::getInstance()->getVisibleSize();
    Vec2 visVec = Director::getInstance()->getVisibleOrigin();

    Vec2 tve(Vec2::ZERO);
    switch (angle)
    {
    case ANGLE_DOWN:
        tve.x = inSP.x;
        break;
    case ANGLE_LEFT:
        tve.y = inSP.y;
        break;
    case ANGLE_RIGHT:
        tve.x = visSize.width;
        tve.y = inSP.y;
        break;
    case ANGLE_UP:
        tve.x = inSP.x;
        tve.y = visSize.height;
        break;
    default:
        break;
    }
    std::vector<CMargin*> allMargin;
    for (int i = 0; i < m_oAllPoint.size()-1;i++)
    {          
        CMargin* pMargin = new CMargin();
        pMargin->setTaget(m_oAllPoint[i], m_oAllPoint[i + 1]);
        allMargin.push_back(pMargin); 
    }
    //----------------------------------------------

    //log("AllMaring:%d", allMargin.size());

    int mindis = -1;
    int tindex = SELECTID_NULL;
    for (int i = 0; i < allMargin.size(); i++)
    {
        CMargin* pMargin = allMargin[i]; 

        int r1 = CUtil::getNextAngle(angle, -1);
        int r2 = CUtil::getNextAngle(angle, 1);

        if (r1 != pMargin->m_Angle && r2 != pMargin->m_Angle)
        {
            continue;
        }

        if (CMath::hasLineMutlLine(pMargin->m_oStart, pMargin->m_oTaget, inSP, tve))
        {
            int dis = static_cast<int>(CMath::getPointToLineDis(pMargin->m_oStart, pMargin->m_oTaget, inSP));

            if (dis == 0)
            {
                continue;
            }

            //log("dis:%d", dis);
            if (mindis == -1 || dis < mindis)
            {
                mindis = dis;
                tindex = i;
            }
        }        
    }            

    int currentdis = static_cast<int>(ccpDistance(inCP, inSP));

    //log("MiniDis:%d  CurrentDis:%d", mindis, currentdis);

    if (mindis != -1 && currentdis > mindis)
    {

        inCP = CMath::getVec2(inSP, mindis - GRAD_CELL, CMath::angleToRadian(angle));
        CUtil::formartGrid(inCP);
        //log("inCP:%f,%f", inCP.x, inCP.y);

        return true;
    }


    //-----------------------------------------------
    for (int i = 0; i < allMargin.size(); i++)
    {
        delete allMargin[i];
    }                      
    return false;
}



bool CPath::hasEndInBegin()
{
    if (m_oAllPoint.size() > 1)
    {
        const Vec2& startP = *(m_oAllPoint.begin());
        const Vec2& endP = *(m_oAllPoint.end() - 1);

        if (startP == endP)
        {                                
            return true;
        }
    }

    return false;
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
//     if (m_oAllPoint.size() > 3)
//     {               
//         //const Vec2& vD1         = *(m_oAllPoint.end() - 2);
//         //const Vec2& vD2         = *(m_oAllPoint.end() - 1);
//         //int pathCurrentDirect   = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(vD1, vD2)));      
//         //outDirect.push_back(CUtil::getRevceDircet(pathCurrentDirect));
//         //log("%d~~~~~~~%f, %f", pathCurrentDirect, inPoint.x, inPoint.y);
// 
//         Vec2 nextStep = CMath::getVec2(inPoint, GRAD_CELL, CMath::angleToRadian(currentDirect));
//         CUtil::formartGrid(nextStep);
// 
//         //log("currentDirect:%d, nextStep:%f,%f", currentDirect, nextStep.x, nextStep.y);
//         
//         if (!hasPointInLine(nextStep))
//         {
//             outDirect.push_back(currentDirect);
//         }    
// 
//         return;
//     }


    
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