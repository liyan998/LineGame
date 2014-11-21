#include "Path.h"   
#include "util/Math.h"
#include "Margin.h"

int CPath::DIRECT[MAXDIRECT][DIRECT_SELECT] =
{
    //angle ,逆时针，   顺时针
    { 90,   180,    0 },
    { 0,    90,     -90 },
    { -90,  0,      180 },
    { 180,  -90,    90 }
};



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
	m_oAllPoint.clear();
}


// 大于0为顺时针
// 小于0为逆时针
int CPath::getDirect()
{
    std::vector<CMargin*> allMargin;
    //log("size:%d", m_oAllPoint.size());
    for (int i = 0; i < m_oAllPoint.size()-1; i++)
    {
        CMargin* tmarg = new CMargin();
        if (i + 1 < m_oAllPoint.size())
        {
            tmarg->setTaget(m_oAllPoint[i], m_oAllPoint[i + 1]);
        }      
        allMargin.push_back(tmarg);
    }
    //----------------------------------------------------------------
    int direct          = 0;
    int currentDirect   = ANGLE_NONE;
    for (int i = 0; i < allMargin.size();i++)
    {
        if (currentDirect == ANGLE_NONE)
        {
            currentDirect = allMargin[i]->m_Angle;
        }
        else{           
            int rl = getRL(currentDirect, allMargin[i]->m_Angle);

            if (rl == 1)
            {
                direct++;
            }
            else if(rl == -1){
                direct--;
            }              
            /*log("direct: %d", direct);*/
            currentDirect = allMargin[i]->m_Angle;
        }
        //log("%d --\t %d", i, allMargin[i]->m_Angle);
    }    
    
    for (int i = 0; i < allMargin.size(); i++)
    {
       delete allMargin[i];
    }
    return direct;
}


int CPath::getRL(int currentDirect, int angle)
{
   

    for (int i = 0; i < 4;i++)
    {
        if (currentDirect == DIRECT[i][0])
        {
            if (angle == DIRECT[i][1])
            {
                return -1;
            }else if(angle == DIRECT[i][2]){
                return 1;
            }
        }
    }
}