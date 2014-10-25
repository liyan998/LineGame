#ifndef __TEST_H__
#define __TEST_H__

#include "triangulate.h"
#include "framework/ui/AGameScene.h"

class CTest : public liyan998::CAGameScene
{
public:
	CREATE_FUNC(CTest)

	virtual bool init();

	void flush();

	bool onTouchBegan(Touch* touches, Event *event);

	void onTouchEnded(Touch* touches, Event *event);

	void onTouchMove(Touch* touches, Event *event);

	void menuCloseCallback(Ref* pSender);

	Vector2dVector allpoint;

	DrawNode* m_Dn;
};


#endif