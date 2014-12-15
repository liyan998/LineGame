/************************************************************************/
/* 


*/
/************************************************************************/
#include "Util.h"

#include <iterator>
#include <algorithm> 

#include "Math.h"
#include "../Margin.h"
#include "../Path.h"


using namespace liyan998;


bool CUtil::hasPointInPloyon(const std::vector<Vec2>& refVector,const Vec2& refPoint)
{ 
    unsigned int count = 0;
    int polySides = refVector.size();

    std::vector<float>  polyX;
    std::vector<float>  polyY;

    for (int i = 0; i < refVector.size(); i++)
    {
        polyX.push_back(refVector[i].x);
        polyY.push_back(refVector[i].y);
    }

    float x         = refPoint.x;
    float y         = refPoint.y;

    int j           = polySides - 1;
    bool  oddNodes  = false;

    for (int i = 0; i < polySides; i++)
    {
        if ((polyY[i] < y && polyY[j] >= y || polyY[j] < y && polyY[i] >= y)
            &&
            (polyX[i] <= x || polyX[j] <= x)
            )
        {
            oddNodes ^= (polyX[i] + (y - polyY[i]) / (polyY[j] - polyY[i])*(polyX[j] - polyX[i]) < x);
        }
        j = i;
    }

    return oddNodes; 
}


unsigned int CUtil::getCountPointInPloyon(std::vector<Vec2>& refPloyon, std::vector<Vec2>& refAllPoint)
{
    unsigned int count = 0;

    for (int i = 0; i < refAllPoint.size();i++)
    {
        if (hasPointInPloyon(refPloyon, refAllPoint[i]))
        {
            count++;
        }
    }
    return count;
}

//inRect 被检测多边形
//refRect2 检测多边形
unsigned int CUtil::getCountPointInRec(const std::vector<Vec2>& inRect,const std::vector<Vec2>& refRec2)
{          
    unsigned int count = 0;
    lab:for (int i = 0; i < inRect.size();i++)
    {
       for (int j = 0; j < refRec2.size();j++)
       {
          if (inRect[i] == refRec2[j])
          {
              count++;              
          }
          else if (hasPointInPloyon(refRec2, inRect[i]))
          {
              count++;
          } 
       } 
    }
    return count;
}

bool CUtil::hasPointInLine(const Vec2& lineP1, const Vec2& lineP2, const Vec2& outPoint)
{          //     Vec2 point[MAX];
//     point[0] = lineP1;
//     point[1] = lineP2;
//     point[2] = outPoint;
// 
//     for (int i = 0; i < MAX;i++)
//     {
//         liyan998::CMath::getIntPoint(point[i]);
//     }   
 
//     distance[0] = static_cast<int>(ccpDistance(point[0], point[2]));
//     distance[1] = static_cast<int>(ccpDistance(point[1], point[2]));
//     distance[2] = static_cast<int>(ccpDistance(point[0], point[1]));
    float dis = getDisPointLine(lineP1, lineP2, outPoint);
    //log("line dis:%f", dis);
    if (dis < 0.01f)
    {                                                  
        return true;
    }  
    return false;
}


float CUtil::getDisPointLine(const Vec2& lineP1, const Vec2& lineP2, const Vec2& outPoint)
{
    const int MAX = 3;
    float distance[MAX];

    distance[0] = ccpDistance(lineP1, outPoint);
    distance[1] = ccpDistance(lineP2, outPoint);
    distance[2] = ccpDistance(lineP1, lineP2);

    return distance[1] + distance[0] - distance[2];   
}

void CUtil::getSubVector(const std::vector<Vec2>& resource, int start, int end, std::vector<Vec2>& result)
{
    std::vector<Vec2>::const_iterator  it = resource.begin();
    if (start > end)
    {
        std::copy(it + start, resource.end(), std::back_inserter(result));
        std::copy(it, it + end + 1, std::back_inserter(result));
    }
    else
    {
        std::copy(it + start, it + end + 1, std::back_inserter(result));
    }
}


/*********************************************************************/
/*
* @brief        
* @param[in]    direct      

* @param[out]
* @return       
*/
/*********************************************************************/
int CUtil::getRevceDircet(int direct)
{
    //log("%d", (direct == ANGLE_UP) && (fixangle == ANGLE_DOWN)); 
    switch (direct)
    {
    case ANGLE_LEFT:
        return ANGLE_RIGHT;
    case ANGLE_RIGHT:
        return ANGLE_LEFT;
    case ANGLE_DOWN:
        return ANGLE_UP;
    case ANGLE_UP:
        return ANGLE_DOWN;
    }                
    return ANGLE_NONE;
}

int CUtil::getRotateDirect(const std::vector<Vec2>& allpoint, const std::vector<Vec2>& path)
{
	
	int result = getRotateDirect(path);

	if (result != 0)
	{
		return result;
	}

	/////////////////////////////////////////////////////
	/*
	Vec2 starpoint = *path.begin();
	Vec2 endpoint = *(path.end() - 1);
	
	int startindex	= -1;
	int endindex	= -1;


	for (int i = 0; i < allpoint.size(); i++)
	{
		if (starpoint == allpoint[i])
		{
			startindex = i;
		}
		else if (endpoint == allpoint[i])
		{
			endindex = i;
		}
	}
	*/

	return 0;
}

/*********************************************************************/
/**
* @brief        得到多边形方向
* @param[in]    allpoint

* @param[out]
* @return       int 返回方向值 -1 or 1
*/
/*********************************************************************/
int CUtil::getRotateDirect(const std::vector<Vec2>& allpoint)
{
	if (allpoint.size() == 0)
	{
		return 0;
	}

	std::vector<CMargin*> allMargin;
	//log("size:%d", m_oAllPoint.size());
	for (int i = 0; i < allpoint.size()-1; i++)
	{
		CMargin* tmarg = new CMargin();
		if (i + 1 < allpoint.size())
		{
			tmarg->setTaget(allpoint[i], allpoint[i + 1]);
		}      
		allMargin.push_back(tmarg);
	}

	int direct          = 0;
	int currentDirect   = ANGLE_NONE;
	for (int i = 0; i < allMargin.size();i++)
	{
		if (currentDirect == ANGLE_NONE)
		{
			currentDirect = allMargin[i]->m_Angle;
		}
		else{           
			int rl = getRL(currentDirect, allMargin[i]->m_Angle);

			if (rl == 1)
			{
				direct++;
			}
			else if(rl == -1){
				direct--;
			}              
			//log("direct: %d", direct);
			currentDirect = allMargin[i]->m_Angle;
		}
		//log("%d --\t %d", i, allMargin[i]->m_Angle);
	}    

	for (int i = 0; i < allMargin.size(); i++)
	{
		delete allMargin[i];
	}


	if (direct > 0)
	{
		return DIRECT_CLOCKWISE;
	}else if (direct < 0)
	{
		return DIRECT_ANTICCLOCKWISE;
	}	
	return 0;
}

/*********************************************************************/
/**
* @brief        得到方向权值
* @param[in]    int currentDirect   当前方向
int angle           下一个角度
* @param[out]
* @return       int 返回方向权值 -1 or 1
*/
/*********************************************************************/
int CUtil::getRL(int currentDirect, int angle)
{
	for (int i = 0; i < 4;i++)
	{
		if (currentDirect == CPath::DIRECT[i][0])
		{
			if (angle == CPath::DIRECT[i][1])
			{
				return -1;
			}else if(angle == CPath::DIRECT[i][2]){
				return 1;
			}
		}
	}
}

/*********************************************************************/
/*
* @brief        转换方向值为flag值
* @param[in]    inDirect 方向值

* @param[out]
* @return       unsigned int flag
                F F F F
                上下左右 
                90, -90, 180 ,0
*/
/*********************************************************************/
unsigned int CUtil::converDirectToFlag(int inDirect)
{                
    switch (inDirect)
    {
    case ANGLE_UP:
        return FLAG_UP;
    case ANGLE_DOWN:
        return FLAG_DOWN;
    case ANGLE_LEFT:
        return FLAG_LEFT;
    case ANGLE_RIGHT:
        return FLAG_RIGHT;
    }
    return ANGLE_NONE;
}

int CUtil::converFlagToDirect(unsigned int inFlag)
{                 
    switch (inFlag)
    {
    case FLAG_UP:
        return ANGLE_UP;        
    case FLAG_DOWN:
        return ANGLE_DOWN;
    case FLAG_LEFT:
        return ANGLE_LEFT;
    case FLAG_RIGHT:
        return ANGLE_RIGHT;
    }
    return ANGLE_NONE;
}


/*********************************************************************/
/*
* @brief        从flag中得到方向集
* @param[in]    inFlag      flag方向

* @param[out]   outDirects  方向集合
* @return       void  
*/
/*********************************************************************/
void CUtil::getDirectFromFlag(unsigned int inFlag, std::vector<int>& outDirects)
{
    unsigned int vb = 0xF;
    for (int i = 0; i < 4;i++)
    {                
        unsigned int parm = vb << (4 * i);
        unsigned int result = inFlag & parm;

        if (result != 0)
        {
            outDirects.push_back(converFlagToDirect(result));
        }              
    }
}

/*********************************************************************/
/*
* @brief        格式化坐标位置
* @param[in]    inPoint     flag方向

* @param[out]   
* @return       void
*/
/*********************************************************************/
void CUtil::formartGrid(Vec2& inPoint)
{                                          
    formartGrid(inPoint, GRAD_CELL);
}

void CUtil::formartGrid(Vec2& inoutPoint, int grid)
{
    inoutPoint.x = FTOI(inoutPoint.x) / grid * grid;
    inoutPoint.y = FTOI(inoutPoint.y) / grid * grid;
}


//根据当前方向得到权值对应方向，权值为顺时1，逆时-1
int CUtil::getNextAngle(int currentangle, int d)
{
#define MAX_ANGLE 4
    int anglelist[MAX_ANGLE] =
    {
        ANGLE_LEFT,
        ANGLE_UP,
        ANGLE_RIGHT,
        ANGLE_DOWN
    };
    int currentindex = 0;
    int selectindex = 0;

    for (int i = 0; i < MAX_ANGLE; i++)
    {
        if (currentangle == anglelist[i])
        {
            currentindex = i;
        }
    }

    if (currentindex + d >= MAX_ANGLE)
    {
        selectindex = 0;
    }
    else if (currentindex + d < 0)
    {
        selectindex = MAX_ANGLE - 1;
    }
    else
    {
        selectindex = currentindex + d;
    }
    return anglelist[selectindex];
}


/************************************************************************/
/* 

* @brief        得到与inSP最近障碍物距离
* @param[in]    inSP            当前位置
                inAllMargin     所有边
                angle           角度
* @param[out]
* @return       void

*/
/************************************************************************/
int CUtil::getMinWallDis(const std::vector<CMargin*>& inAllMargin, const Vec2& inSP,int angle)
{

    Size visSize = Director::getInstance()->getVisibleSize();
    Vec2 visVec = Director::getInstance()->getVisibleOrigin();

    //log("-------------------------------------------");

    //auto director = Director::getInstance();
    //Size size;
    //size = director->getWinSize();
    //log("***IDONG: Director getWinSize:w=%f,h=%f", size.width, size.height);

    //size = director->getWinSizeInPixels();
    //log("***IDONG: Director getWinSizeInPixels:w=%f,h=%f", size.width, size.height);

    //size = director->getVisibleSize();
    //log("***IDONG: Director getVisibleSize:w=%f,h=%f", size.width, size.height);

    //Point point = director->getVisibleOrigin();
//     log("***IDONG: Director getVisibleOrigin:x=%f,y=%f", point.x, point.y);
// 
//     log("VisSize:%f, %f  Visibleorigin::%f, %f", visSize.width, visSize.height, visVec.x ,visVec.y);
    Vec2 tve(Vec2::ZERO);
    switch (angle)
    {
    case ANGLE_DOWN:
        tve.x = inSP.x;
       // tve.y = visVec.y;
        break;
    case ANGLE_LEFT:
        //tve.x = visVec.x;
        tve.y = inSP.y;
        break;
    case ANGLE_RIGHT:
        tve.x = visSize.width + visVec.x;
        tve.y = inSP.y;
        break;
    case ANGLE_UP:
        tve.x = inSP.x + visVec.x;
        tve.y = visSize.height + visVec.y;
        break;
    default:
        break;
    }

    int mindis = -1;
   
    for (int i = 0; i < inAllMargin.size(); i++)
    {
        CMargin* maring = inAllMargin[i];

        int r1 = CUtil::getNextAngle(angle, -1);
        int r2 = CUtil::getNextAngle(angle, 1);

        if (r1 != maring->m_Angle && r2 != maring->m_Angle)
        {
            continue;
        } 
       // log("p1: %f,%f \n  p2:%f,%f  \n p3:%f,%f \n p4:%f, %f", maring->m_oStart.x, maring->m_oStart.y, maring->m_oTaget.x, maring->m_oTaget.y, inSP.x, inSP.y, tve.x, tve.y);
        if (liyan998::CMath::hasLineMutlLine(maring->m_oStart, maring->m_oTaget, inSP, tve))
        {

            Vec2 zu = CMath::getFootPoint(maring->m_oStart, maring->m_oTaget, inSP);         

            int dis = static_cast<int>(ccpDistance(inSP, zu));

            if (dis == 0)
            {
                continue;
            }

            //log("CUtil dis:%d", dis);
            if (mindis == -1 || dis < mindis)
            {
                mindis = dis;                 
            }
        }
    }  
    return mindis;
}


int CUtil::getUDLR_atMarginDis(CMargin* pMaring, const Vec2& inPoint  , int direct)
{
    Size visSize = Director::getInstance()->getVisibleSize();
    Vec2 visVec = Director::getInstance()->getVisibleOrigin();

    Vec2 tve(Vec2::ZERO);
    switch (direct)
    {
    case ANGLE_DOWN:
        tve.x = inPoint.x;
        // tve.y = visVec.y;
        break;
    case ANGLE_LEFT:
        //tve.x = visVec.x;
        tve.y = inPoint.y;
        break;
    case ANGLE_RIGHT:
        tve.x = visSize.width + visVec.x;
        tve.y = inPoint.y;
        break;
    case ANGLE_UP:
        tve.x = inPoint.x + visVec.x;
        tve.y = visSize.height + visVec.y;
        break;
    default:
        break;
    }
    
    if (CMath::hasLineMutlLine(pMaring->m_oStart, pMaring->m_oTaget, inPoint, tve))
    { 
        Vec2 zu = CMath::getFootPoint(pMaring->m_oStart, pMaring->m_oTaget, inPoint);
        return ccpDistance(inPoint, zu);
    } 

    return -1;
}


/************************************************************************/
/*

* @brief        得到修正后的方向

* @param[in]    currentdirect       向量方向
* @param[in]    direct       向量方向

* @return       int         修正后的方向

*/
/************************************************************************/
int CUtil::getFixDirect(int currentdirect ,int angle)
{                            
    int errorMarign = 45;      
    int angleList[] = { 90, 0, -90, 180, 270 };
    int size = sizeof(angleList) / sizeof(angleList[0]);
    for (int i = 0; i < size; i++)
    {
        if (angleList[i] == angle)
        {
            return angle;
        }
        else if (abs(angle - angleList[i]) < errorMarign)
        {
            if (angleList[i] == 270)
            {
                return -90;
            }
            return angleList[i];
        }
    }
    switch (currentdirect)
    {
    case ANGLE_DOWN:
        if (angle >= ANGLE_DOWN + errorMarign && angle <= ANGLE_RIGHT - errorMarign)
        {
            //->down | right
            log("down | right");
            return ANGLE_RIGHT;
        }
        else if (angle >= ANGLE_LEFT - errorMarign && angle <= ANGLE_LEFT * 2 - errorMarign)
        {
            //->down | left
            log("down | left");
            return ANGLE_LEFT;
        }
        break;
    case ANGLE_UP:
        if (angle >= ANGLE_RIGHT + errorMarign && angle <= ANGLE_UP - errorMarign)
        {
            //-> up | right
            log("up | right");
            return ANGLE_RIGHT;
        }
        else if (angle >= ANGLE_UP + errorMarign && angle <= ANGLE_LEFT - errorMarign)
        {
            //-> up | left
            log("up | left");
            return ANGLE_LEFT;
        }
        break;
    case ANGLE_LEFT:
        if (angle >= ANGLE_LEFT + errorMarign && angle <= ANGLE_LEFT + 90 - errorMarign)
        {
            //->left | down
            log("left | down");
            return ANGLE_DOWN;
        }
        else if (angle >= ANGLE_UP + errorMarign && angle <= ANGLE_LEFT - errorMarign)
        {
            //->left | up
            log("left | up");
            return ANGLE_UP;
        }
        break;
    case ANGLE_RIGHT:
        if (angle >= ANGLE_DOWN + errorMarign && angle <= ANGLE_RIGHT - errorMarign)
        {
            //-> right | down
            log("right | down");
            return ANGLE_DOWN;
        }
        else if (angle >= ANGLE_RIGHT + errorMarign && angle <= ANGLE_UP - errorMarign)
        {
            //-> right | up
            log("right | up");
            return ANGLE_UP;
        }
        break;
    }
    return ANGLE_ERROR;
}


int CUtil::getFixDictance(int direct, const Vec2& startP, const Vec2& endP)
{

    //根据方向得到 距离

    if (direct == ANGLE_NONE || direct == ANGLE_ERROR)
    {
        return 0;
    }
    int distance = 0;

    if (ANGLE_UP == abs(direct))
    {
        //log("up down");        
        distance = static_cast<int>(abs(startP.y - endP.y));
    }
    else{
        //log("right left");
        distance = static_cast<int>(abs(startP.x - endP.x));
    }
    return distance;


}