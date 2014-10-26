#include "Test.h"



bool CTest::init()
{
	Layer::init();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	m_Dn = DrawNode::create();
	addChild(m_Dn);

	auto lisnter = EventListenerTouchOneByOne::create();

	//git test

	lisnter->onTouchBegan = CC_CALLBACK_2(CTest::onTouchBegan, this);
	lisnter->onTouchEnded = CC_CALLBACK_2(CTest::onTouchEnded, this);
	lisnter->onTouchMoved = CC_CALLBACK_2(CTest::onTouchMove, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(lisnter, this);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CTest::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}


void CTest::flush()
{
	m_Dn->clear();
	
	Vector2dVector vv;
	Triangulate::Process(allpoint, vv);	

	int tcount = vv.size()/3;
	for (int i=0; i<tcount; i++)
	{
		const Vector2d &p1 = vv[i * 3 + 0];
		const Vector2d &p2 = vv[i * 3 + 1];
		const Vector2d &p3 = vv[i * 3 + 2];		
		m_Dn->drawTriangle(Vec2(p1.GetX(), p1.GetY()),Vec2(p2.GetX(), p2.GetY()),Vec2(p3.GetX(), p3.GetY()),Color4F(1,1,0,1));
	}

	for (int i =0;i < allpoint.size();i++)
	{		
		m_Dn->drawDot(Vec2(allpoint[i].GetX(),allpoint[i].GetY()), 3, Color4F(1,1,1,1));
	}
	
}


bool CTest::onTouchBegan(Touch* touches, Event *event)
{

	auto local = touches->getLocation();



	allpoint.push_back(Vector2d(local.x,local.y));


	flush();
	return true;

}


void CTest::onTouchEnded(Touch* touches, Event *event)
{


}


void CTest::onTouchMove(Touch* touches, Event *event)
{


}

void CTest::menuCloseCallback(Ref* pSender){
	flush();

	allpoint.clear();
}