#ifndef __MATH_H__
#define __MATH_H__

#include <math.h>     

#include "../System.h"

namespace liyan998
{




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

        //�õ�����
        static Vec2 getFootPoint(const Vec2& lineP1, const Vec2& lineP2, const Vec2& lineOP);

        //�㵽ֱ�ߵľ���
        static float getPointToLineDis(const Vec2& pt1, const Vec2& pt2, const Vec2& pt3);

        //Vec2ȥ������
        static void getIntPoint(Vec2& inPoint);


        //���׹�ʽ�����������
        static float getTraingleArea(const Vec2& p1, const Vec2& p2, const Vec2& p3);

        //��������߶��Ƿ��ཻ
        static bool hasLineMutlLine(const Vec2& pa1, const Vec2& pa2, const Vec2& pb1, const Vec2& pb2);

        //���
        static float mult(const Vec2& pa, const Vec2& pb, const Vec2& pc);
    
    };
}


#endif//__MATH_H__