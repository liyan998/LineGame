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

        //�õ�һ������
        static Vec2 getVec2(const Vec2& rStart, float step, float angle);

        //�õ�һ������
        static float getRadian(const Vec2& rStart, const Vec2& rEnd);

        //����ת�Ƕ�
        static float radianToAngle(float radian);

        //�Ƕ�ת����
        static float angleToRadian(float angle);

        //�õ������
        static int getRandom(int startI, int endI);

    };
}


#endif//__MATH_H__