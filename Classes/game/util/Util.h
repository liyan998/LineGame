#ifndef __UTIL_H__
#define __UTIL_H__

#include "../System.h"

class CUtil
{
public:

    //���Ƿ���ployon��
    static bool hasPointInPloyon(std::vector<Vec2>& refVector,const Vec2& refPoint);
 
    //������ployon�ڵĵ����
    static unsigned int getCountPointInPloyon(std::vector<Vec2>& refPloyon, std::vector<Vec2>& refAllPoint);

    //���Ƿ����߶���
    static bool hasPointInLine(const Vec2& lineP1, const Vec2& lineP2, const Vec2& outPoint);

    //��õ���ֱ�ߵ�λ�ù�ϵ
    static float getDisPointLine(const Vec2& lineP1, const Vec2& lineP2, const Vec2& outPoint);

    //�õ���vector
    static void getSubVector(const std::vector<Vec2>& resource, int start, int end, std::vector<Vec2>& result);


};
 

#endif//__UTIL_H__