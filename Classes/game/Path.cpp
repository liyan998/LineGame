#include "Path.h"
#include "framework/util/Math.h"

void CPath::addPoint(const Vec2& vec2 )
{
    int x = static_cast<int>(vec2.x);
    int y = static_cast<int>(vec2.y);

    if (m_oAllPoint.size() > 0)
    {
        const Vec2& tv = m_oAllPoint[m_oAllPoint.size() - 1];

        int tx = static_cast<int>(tv.x);
        int ty = static_cast<int>(tv.y);
        if (x == tx && y == ty)
        {
            return;
        }
    }

    log("=====new Point: %d, %d", x, y);
	m_oAllPoint.push_back(Vec2(x, y));	
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
    float rC = liyan998::CMath::getRandom(1, 100) / 100.f;
    float gC = liyan998::CMath::getRandom(1, 100) / 100.f;
    float bC = liyan998::CMath::getRandom(1, 100) / 100.f;


	for (int i = 0 ;i < m_oAllPoint.size();i++)
    {
        dn->drawDot(m_oAllPoint[i], 4, Color4F(1, 0, 0, 1));
        dn->drawDot(m_oAllPoint[i], 3, Color4F(rC, gC, bC, 1));        
	}
}

void CPath::clearPoint()
{
//     log("--------------------------------------------");
//     for (int i = 0; i < m_oAllPoint.size(); i++)
//     {
//         log("Vec2(%f, %f),", m_oAllPoint[i].x, m_oAllPoint[i].y);
//     }
	m_oAllPoint.clear();
}