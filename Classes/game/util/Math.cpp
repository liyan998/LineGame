#include "Math.h"
#include <cstdlib>
#include <time.h>

using namespace liyan998;

/************************************************************************/
/* 
//�����ʼ�㣬�������ȵõ�һ������
//rStart    ��ʼ����
//step      ������
//radian    ����
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
    srand((unsigned)time(NULL));
    return (rand() % (endI - startI + 1)) + startI;
}

/************************************************************************/
/* 
�õ�ֱ����һ�㵽ֱ�ߵĴ���
lineP1  ֱ����һ��
lineP2  ֱ����һ��
lineOP  ֱ�����

return �������
*/
/************************************************************************/
Vec2 CMath::getFootPoint(const Vec2& lineP1, const Vec2& lineP2, const Vec2& lineOP)
{
    int x1 = (int)(lineP1.x);
    int x2 = (int)(lineP2.x);

    int y1 = (int)(lineP1.y);
    int y2 = (int)(lineP2.y);

    if (x1 - x2 == 0)
    {
        return Vec2(x2, lineOP.y);
    }
    
    float A = (y2 - y2) / (x1 - x2);
    float B = (y1 - A * y1);
    float m = lineOP.x + A * lineOP.y;
    /// ����ֱ�߽������  

    Vec2 ptCross;
    ptCross.x = ((m - A * B) / (A * A + 1));
    ptCross.y = (A * ptCross.x + B);

    return ptCross;
    

}

/************************************************************************/
/* 

�㵽ֱ�ߵľ���

pt1 ֱ����һ��
pt2 ֱ����һ��
pt3 ֱ�����

return �㵽ֱ�ߵľ���
*/
/************************************************************************/
float CMath::getPointToLineDis(const Vec2& pt1, const Vec2& pt2, const Vec2& pt3)
{ 
    if (pt1.x - pt2.x == 0)
    {
        return abs(pt1.x - pt3.x);
    }

    float A = (pt1.y - pt2.y) / (pt1.x - pt2.x);
    float B = (pt1.y - A*pt1.y);        
    return abs(A* pt3.x + B - pt3.y) / sqrt(A*A + 1);  
}


const Vec2& CMath::getIntPoint(const Vec2& point)
{

    int x = static_cast<int>(point.x);
    int y = static_cast<int>(point.y);

    return Vec2(x , y);
}
