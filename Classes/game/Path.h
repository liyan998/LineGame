#ifndef __PATH_H__
#define __PATH_H__

#include "framework/System.h"
#include "Rander.h"

class CPath : public CRander
{
public:

	void addPoint(const Vec2& vec2 );

	void clearPoint();	

	virtual void print(DrawNode* dn);

public:
	
	std::vector< Vec2 > m_oAllPoint;
};

#endif//__PATH_H__