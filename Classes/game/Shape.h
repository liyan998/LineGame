/************************************************************************/
/* 


*/
/************************************************************************/
#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "framework/System.h"

class CShape 
{
public:

	CShape();

	~CShape();

public:

	void draw(DrawNode* drawNode);

	void setShape(const std::vector<Vec2>& link);

private:

	std::vector<Vec2>	m_oPoints;

};
#endif//__SHAPE_H__