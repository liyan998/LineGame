#ifndef __UTIL_H__
#define __UTIL_H__

#include "framework/System.h"

class CUtil
{
public:

    static bool hasPointInPloyon(std::vector<Vec2>& refVector, Vec2& refPoint);
 
    static unsigned int getCountPointInPloyon(std::vector<Vec2>& refPloyon, std::vector<Vec2>& refAllPoint);
};
 

#endif//__UTIL_H__