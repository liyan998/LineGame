#ifndef __UTIL_H__
#define __UTIL_H__

#include "framework/System.h"

class CUtil
{
public:

    static bool hasPointInPloyon(std::vector<Vec2>& refVector,const Vec2& refPoint);
 
    static unsigned int getCountPointInPloyon(std::vector<Vec2>& refPloyon, std::vector<Vec2>& refAllPoint);

    static bool hasPointInLine(const Vec2& lineP1, const Vec2& lineP2, const Vec2& outPoint);
};
 

#endif//__UTIL_H__