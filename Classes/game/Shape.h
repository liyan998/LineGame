#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "framework/System.h"
#include "triangulate.h"

class CShape
{
public:

    void draw(DrawNode* pDd);                       //渲染

    void setShape(std::vector<Vec2>& allPoint);     //设置节点

public:

    Vector2dVector  m_AllPoint;                     //多边形节点
};

#endif//__SHAPE_H__