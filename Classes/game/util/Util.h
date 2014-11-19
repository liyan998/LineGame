#ifndef __UTIL_H__
#define __UTIL_H__

#include "../System.h"

class CUtil
{
public:

    //点是否在ployon内
    static bool hasPointInPloyon(std::vector<Vec2>& refVector,const Vec2& refPoint);
 
    //返回在ployon内的点个数
    static unsigned int getCountPointInPloyon(std::vector<Vec2>& refPloyon, std::vector<Vec2>& refAllPoint);

    //点是否在线段内
    static bool hasPointInLine(const Vec2& lineP1, const Vec2& lineP2, const Vec2& outPoint);

    //获得点与直线的位置关系
    static float getDisPointLine(const Vec2& lineP1, const Vec2& lineP2, const Vec2& outPoint);

    //得到子vector
    static void getSubVector(const std::vector<Vec2>& resource, int start, int end, std::vector<Vec2>& result);


};
 

#endif//__UTIL_H__