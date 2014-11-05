#include "Test.h"
#include "util/Math.h"



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

  





}



bool CTest::onTouchBegan(Touch* touches, Event *event)
{
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


}
