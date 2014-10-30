#include "Path.h"


void CPath::addPoint(const Vec2& vec2 )
{
	log("new Point: %f, %f", vec2.x, vec2.y);
	m_oAllPoint.push_back(vec2);	
}



void CPath::print( DrawNode* dn)
{
	for (int i = 0; i < m_oAllPoint.size(); i++)
	{
		if (i + 1 < m_oAllPoint.size())
		{
			dn->drawSegment(m_oAllPoint[i], m_oAllPoint[i + 1], 2, Color4F(0, .5F, .5F, .5F));
		}       
	}
	for (int i = 0 ;i < m_oAllPoint.size();i++)
	{		
		dn->drawDot(m_oAllPoint[i],2,Color4F(1,0,0,1));
	}
}

void CPath::clearPoint()
{
	m_oAllPoint.clear();
}