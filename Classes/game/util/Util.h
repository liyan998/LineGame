#ifndef __UTIL_H__
#define __UTIL_H__

#include "../System.h"
#include "../Margin.h"

class CUtil
{
public:

    //点是否在ployon内
    static bool hasPointInPloyon(const std::vector<Vec2>& refVector,const Vec2& refPoint);
 
    //返回在ployon内的点个数
    static unsigned int getCountPointInPloyon(std::vector<Vec2>& refPloyon, std::vector<Vec2>& refAllPoint);

    //返回一个集合包含另一个集合个数
    static unsigned int getCountPointInRec(const std::vector<Vec2>& refRec1, const std::vector<Vec2>& refRec2);
    
    //点是否在线段内
    static bool hasPointInLine(const Vec2& lineP1, const Vec2& lineP2, const Vec2& outPoint);

    //获得点与直线的位置关系
    static float getDisPointLine(const Vec2& lineP1, const Vec2& lineP2, const Vec2& outPoint);

    //得到子vector
    static void getSubVector(const std::vector<Vec2>& resource, int start, int end, std::vector<Vec2>& result);
    
    //得到相向而行方向
    static int getRevceDircet(int direct);

	//得到旋转方向
	static int getRotateDirect(const std::vector<Vec2>& allpoint);
	static int getRotateDirect(const std::vector<Vec2>&allpoint, const std::vector<Vec2>&path);	
	static int getRL(int currentDirect, int angle);

    //转换方向值
    static unsigned int converDirectToFlag(int inDirect);
    static int converFlagToDirect(unsigned int inFlag);

    //得到方向集
    static void getDirectFromFlag(unsigned int inFlag , std::vector<int>& outDirects);

    //格式化坐标
    static void formartGrid(Vec2& inoutPoint);

    static void formartGrid(Vec2& inoutPoint, int grid);

    //与屏幕匹配
    //static Vec2 originPosition(const Vec2& inPoint);

    //根据当前方向得到权值对应方向，权值为顺时1，逆时-1
    static int getNextAngle(int currentangle, int d);

    //得到最小障碍距离
    static int getMinWallDis(const std::vector<CMargin*>& inAllMargin, const Vec2& inSP,int angle);
    static int getUDLR_atMarginDis(CMargin* pMaring ,const Vec2& inPoint, int direct);

    //得到FIX后的方向
    static int getFixDirect(int currentdirect, int angle);

    //得到距离
    static int getFixDictance(int direct, const Vec2& startP, const Vec2& endP);


};


 

#endif//__UTIL_H__