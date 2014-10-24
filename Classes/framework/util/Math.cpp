#include "Math.h"
#include <cstdlib>


using namespace liyan998;

/************************************************************************/
/* 
//������ʼ�㣬�������ȵõ�һ������
//rStart    ��ʼ����
//step      ������
//radian     ����
//return    ����
*/
/************************************************************************/
Vec2 CMath::getVec2(const Vec2& rStart,float step, float radian)
{
    Vec2 rEnd;

    rEnd.x = rStart.x + cos(radian) * step;
    rEnd.y = rStart.y + sin(radian) * step;

    return rEnd;
}



float CMath::getRadian(const Vec2& v1, const Vec2& v2)
{
    return atan2((v2.x - v1.x), (v2.y - v1.y));
}

float CMath::angleToRadian(float a)
{
    return a * PI / 180;
}

float CMath::radianToAngle(float r)
{
    return r * 180 / PI;
}


int CMath::getRandom(int startI, int endI)
{
    return rand() % (endI - startI + 1) + startI;
}