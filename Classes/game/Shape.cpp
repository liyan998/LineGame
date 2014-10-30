#include "Shape.h"
#include "triangulate.h"

void CShape::draw(DrawNode* pDd)
{    
    Vector2dVector vv;

    Triangulate::Process(m_AllPoint, vv);

    int tcount = vv.size() / 3;
    for (int i = 0; i < tcount; i++)
    {
        const Vector2d &p1 = vv[i * 3 + 0];
        const Vector2d &p2 = vv[i * 3 + 1];
        const Vector2d &p3 = vv[i * 3 + 2];
        Vec2 tvec1[] = 
        {
            Vec2(p1.GetX(), p1.GetY()),
            Vec2(p2.GetX(), p2.GetY()),
            Vec2(p3.GetX(), p3.GetY())
        };
        pDd->drawPolygon(tvec1, 3, Color4F(1, 0, 1, .1f), 0, Color4F(0, 0, 0, 0));
    }
}

void CShape::setShape(std::vector<Vec2>& allPoint)
{
    m_AllPoint.clear();
    for (int i = 0; i < allPoint.size();i++)
    {
        m_AllPoint.push_back(Vector2d(allPoint[i].x, allPoint[i].y));
    }
}