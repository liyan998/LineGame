#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "framework/System.h"
#include "triangulate.h"

class CShape
{
public:

    void draw(DrawNode* pDd);                       //��Ⱦ

    void setShape(std::vector<Vec2>& allPoint);     //���ýڵ�

public:

    Vector2dVector  m_AllPoint;                     //����νڵ�
};

#endif//__SHAPE_H__