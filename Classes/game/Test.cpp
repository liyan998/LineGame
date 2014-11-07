#include "Test.h"
#include "util/Math.h"



bool CTest::init()
{
    Layer::init();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //m_Dn = DrawNode::create();
    //addChild(m_Dn);

    auto lisnter = EventListenerTouchOneByOne::create();

    //git test

    lisnter->onTouchBegan = CC_CALLBACK_2(CTest::onTouchBegan, this);
    lisnter->onTouchEnded = CC_CALLBACK_2(CTest::onTouchEnded, this);
    lisnter->onTouchMoved = CC_CALLBACK_2(CTest::onTouchMove, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(lisnter, this);

    //------------------------------------------------------------------------------------

    m_Dn = DrawNode::create();
    //m_Dn->setAnchorPoint(Vec2(0.5f, 0.5f));
    //m_Dn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    Rect rec(0, 0, 300, 300);
    allpoint.push_back(rec.origin);
    allpoint.push_back(Vec2(rec.origin.x + rec.size.width, rec.origin.y));
    allpoint.push_back(Vec2(rec.origin.x + rec.size.width, rec.origin.y - rec.size.height));
    allpoint.push_back(Vec2(rec.origin.x, rec.origin.y - rec.size.height));

    m_Dn->drawPolygon(&allpoint[0], allpoint.size(), Color4F(1, 1, 1, 1), 0, Color4F(1, 1, 1, 1));
    
    //-----------------------------------------------------------

    ClippingNode* cn = ClippingNode::create();

    //cn->setContentSize(Size(visibleSize.width, visibleSize.height));
    cn->setAnchorPoint(Vec2(0.5, 0.5));
    cn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    cn->setStencil(m_Dn);
    //cn->setInverted(true);
    //cn->setAlphaThreshold(0.05f);

    addChild(cn);

    //----------------------------------------------------

    auto pSprite = Sprite::create("HelloWorld.png");
    //pSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    pSprite->setScale(2.0f);
    cn->addChild(pSprite);
                              


    //---------------------------------------------

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(CTest::menuCloseCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
        origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

  



    //------------------------------------------------


    



	return true;
}


void CTest::flush()
{
	m_Dn->clear();

    allpoint.clear();
  
    Rect rec(0, 0, 30, 300);

    allpoint.push_back(rec.origin);
    allpoint.push_back(Vec2(rec.origin.x + rec.size.width, rec.origin.y));
    allpoint.push_back(Vec2(rec.origin.x + rec.size.width, rec.origin.y - rec.size.height));
    allpoint.push_back(Vec2(rec.origin.x, rec.origin.y - rec.size.height));


    m_Dn->drawPolygon(&allpoint[0], allpoint.size(), Color4F(1, 1, 1, 1), 0, Color4F(1, 1, 1, 1));

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

void CTest::menuCloseCallback(Ref* pSender)
{
	
    flush();
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//     MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
//     return;
// #endif
// 
//     Director::getInstance()->end();
// 
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//     exit(0);
// #endif



}
