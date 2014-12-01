#ifndef __PATH_H__
#define __PATH_H__

#include "System.h"      
#include "Rander.h"

#define MAXDIRECT       4
#define DIRECT_SELECT   3

class CPath : public CRander
{

public:

    static int DIRECT[MAXDIRECT][DIRECT_SELECT];

public:

    virtual void print(DrawNode* dn);

    //-------------------------------------------- 	

	void clearPoint();	

    bool hasEndInBegin();

    //返回可行走区域
    void getMoveAble(
        int currentDirect,
        const Vec2& inPoint,
        std::vector<int>& outDirect
        );

    bool hasOverLoad(const Vec2& inSP, Vec2& outCP, int angle);              //是否闭合过界

private: 

    bool hasPointInLine(const Vec2& inPoint);

public:
	
	std::vector< Vec2 >         m_oAllPoint;

   
};

#endif//__PATH_H__