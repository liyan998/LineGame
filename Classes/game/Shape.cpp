#include "Shape.h"


CShape::CShape()
{


}

CShape::~CShape()
{

}

void CShape::draw(DrawNode* drawNode)
{
	if (m_oPoints.size() < 3)
	{
		log("Shape Point size < 3 == %d", m_oPoints.size());
		return;
	}
	drawNode->drawPolygon(&m_oPoints[0], m_oPoints.size(), Color4F(1, 0, 1, .5f), 1, Color4F(0, 0, 1, 1));
}

void CShape::setShape(const std::vector<Vec2>& link)
{
	std::vector<Vec2>::iterator it = m_oPoints.begin();
	m_oPoints.insert(it, link.begin(), link.end());
}