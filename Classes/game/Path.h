#ifndef __PATH_H__
#define __PATH_H__

#include "System.h"      
#include "Rander.h"

class CPath : public CRander
{
public:

    virtual void print(DrawNode* dn);

    //--------------------------------------------

	void addPoint( const Vec2& vec2 );

	void clearPoint();	

    int getDirect();


    int getRL(int currentDirect, int angle);

public:
	
	std::vector< Vec2 >         m_oAllPoint;

   
};

#endif//__PATH_H__