#include "Math.h"
#include <cstdlib>
#include <time.h>
#include <algorithm>

using namespace liyan998;
using namespace std;

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
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_sec + tv.tv_usec);
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
        //return 0;
        return abs(pt1.x - pt3.x);
    }

    float A = (pt1.y - pt2.y) / (pt1.x - pt2.x);
    float B = (pt1.y - A*pt1.y);        
    return abs(A* pt3.x + B - pt3.y) / sqrt(A*A + 1);  
}


void CMath::getIntPoint(Vec2& point)
{

    int x = static_cast<int>(point.x);
    int y = static_cast<int>(point.y);

    point.x = x;
    point.y = y;

}


float CMath::getTraingleArea(const Vec2& p1, const Vec2& p2, const Vec2& p3)
{          
    const int MAXMARGIN = 3;
    float allMargin[MAXMARGIN];

    allMargin[0] = ccpDistance(p1, p3);
    allMargin[1] = ccpDistance(p1, p2);
    allMargin[2] = ccpDistance(p2, p3);    

    float p = (allMargin[0] + allMargin[1] + allMargin[2]) / 2;


    return sqrt(p * (p - allMargin[0]) * (p - allMargin[1]) * (p - allMargin[2]));

}



bool CMath::hasLineMutlLine(const Vec2& pa1, const Vec2& pa2, const Vec2& pb1, const Vec2& pb2)
{ 
    if (max(pa1.x, pa2.x) < min(pb1.x, pb2.x))
    {
        return false;
    }
    if (max(pa1.y, pa2.y) < min(pb1.y, pb2.y))
    {
        return false;
    }
    if (max(pb1.x, pb2.x) < min(pa1.x, pa2.x))
    {
        return false;
    }
    if (max(pb1.y, pb2.y) < min(pa1.y, pa2.y))
    {
        return false;
    }
    if (mult(pb1, pa2, pa1)*mult(pa2, pb2, pa1) < 0)
    {
        return false;
    }
    if (mult(pa1, pb2, pb1)*mult(pb2, pa2, pb1) < 0)
    {
        return false;
    }
    return true;


}

float CMath::mult(const Vec2& pa, const Vec2& pb, const Vec2& pc)
{                                
    return (pa.x - pc.x) * (pb.y - pc.y) - (pb.x - pc.x) * (pa.y - pc.y);
}
/************************************************************************/
/* 
///------------alg 2------------
//叉积
double mult(Point a, Point b, Point c)
{
return (a.x-c.x)*(b.y-c.y)-(b.x-c.x)*(a.y-c.y);
}

//aa, bb为一条线段两端点 cc, dd为另一条线段的两端点 相交返回true, 不相交返回false
bool intersect(Point aa, Point bb, Point cc, Point dd)
{
if ( max(aa.x, bb.x)<min(cc.x, dd.x) )
{
return false;
}
if ( max(aa.y, bb.y)<min(cc.y, dd.y) )
{
return false;
}
if ( max(cc.x, dd.x)<min(aa.x, bb.x) )
{
return false;
}
if ( max(cc.y, dd.y)<min(aa.y, bb.y) )
{
return false;
}
if ( mult(cc, bb, aa)*mult(bb, dd, aa)<0 )
{
return false;
}
if ( mult(aa, dd, cc)*mult(dd, bb, cc)<0 )
{
return false;
}
return true;
}
///------------alg 2------------

*/
/************************************************************************/
