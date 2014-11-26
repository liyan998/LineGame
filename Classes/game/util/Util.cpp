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
    inPoint.x = GRAD_NUMBER(inPoint.x);
    inPoint.y = GRAD_NUMBER(inPoint.y);
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
