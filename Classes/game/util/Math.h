#ifndef __MATH_H__
#define __MATH_H__

#include <math.h>     

#include "../System.h"

namespace liyan998
{




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

        //得到垂足
        static Vec2 getFootPoint(const Vec2& lineP1, const Vec2& lineP2, const Vec2& lineOP);

        //点到直线的距离
        static float getPointToLineDis(const Vec2& pt1, const Vec2& pt2, const Vec2& pt3);

        //Vec2去掉精度
        static void getIntPoint(Vec2& inPoint);


        //海伦公式求三角形面积
        static float getTraingleArea(const Vec2& p1, const Vec2& p2, const Vec2& p3);

        //叉积两条线段是否相交
        static bool hasLineMutlLine(const Vec2& pa1, const Vec2& pa2, const Vec2& pb1, const Vec2& pb2);

        //叉积
        static float mult(const Vec2& pa, const Vec2& pb, const Vec2& pc);
    
    };
}


#endif//__MATH_H__