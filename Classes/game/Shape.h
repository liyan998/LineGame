#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "System.h"  
#include "util/triangulate.h"

class CShape
{
public:

    void draw(DrawNode* pDd);                       //渲染

    void setColor(Color4F bd, Color4F fill);

    void setShape(std::vector<Vec2>& allPoint);     //设置节点

public:

    Vector2dVector  m_AllPoint;                     //多边形节点

    Color4F         m_bd;
    Color4F         m_fill;
};

#endif//__SHAPE_H__