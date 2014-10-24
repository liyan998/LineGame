#ifndef __MATH_H__
#define __MATH_H__

#include <math.h>
#include "framework/System.h"


namespace liyan998
{


#define PI 3.14159f

    class CMath
    {
    public:

        //得到一个向量
        static Vec2 getVec2(const Vec2& rStart, float step, float angle);

        //得到一个弧度
        static float getRadian(const Vec2& rStart, const Vec2& rEnd);

        //弧度转角度
        static float radianToAngle(float radian);

        //角度转弧度
        static float angleToRadian(float angle);

        //得到随机数
        static int getRandom(int startI, int endI);

    };
}


#endif//__MATH_H__