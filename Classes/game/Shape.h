#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "System.h"  
#include "util/triangulate.h"

class CShape
{
public:

    void draw(DrawNode* pDd);                       //��Ⱦ

    void setColor(Color4F bd, Color4F fill);

    void setShape(std::vector<Vec2>& allPoint);     //���ýڵ�

public:

    Vector2dVector  m_AllPoint;                     //����νڵ�

    Color4F         m_bd;
    Color4F         m_fill;
};

#endif//__SHAPE_H__