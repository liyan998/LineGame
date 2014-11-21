#ifndef __TEST_H__
#define __TEST_H__

#include "util/triangulate.h"

#include "System.h"
#include "Shape.h"

class CTest : public Layer
{
public:
	CREATE_FUNC(CTest)

	virtual bool init();

	void flush();

	bool onTouchBegan(Touch* touches, Event *event);

	void onTouchEnded(Touch* touches, Event *event);

	void onTouchMove(Touch* touches, Event *event);

	void menuCloseCallback(Ref* pSender);

	std::vector<Vec2> allpoint;

	DrawNode* m_Dn;

    CShape* shape;

    Vec2 currentposition;
};


#endif