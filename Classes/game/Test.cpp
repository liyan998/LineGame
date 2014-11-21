#include "Test.h"
#include "util/Math.h"
#include "util/Util.h"

using namespace liyan998;

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
  
    addChild(m_Dn);

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
   

    Rect rec(
        GRAD_NUMBER(visibleSize.width / 2 + origin.x - 40),
        GRAD_NUMBER(visibleSize.height / 2 + origin.y + 40),
        GRAD_NUMBER(80),

        GRAD_NUMBER(80)
        );



    allpoint.push_back(rec.origin);
    allpoint.push_back(Vec2(rec.origin.x + rec.size.width, rec.origin.y));
    allpoint.push_back(Vec2(rec.origin.x + rec.size.width, rec.origin.y - rec.size.height));
    allpoint.push_back(Vec2(rec.origin.x, rec.origin.y - rec.size.height));

    
    shape = new CShape();
    shape->setColor(Color4F(1, 1, 0.5, .4), Color4F(1, 1, 0.5, .2));
    shape->setShape(allpoint);


	return true;
}


void CTest::flush()
{                   



    log("currentPosition:%f, %f", currentposition.x, currentposition.y);
    if (CUtil::hasPointInPloyon(allpoint, currentposition))
    {
        log("in Ployon");
    }
    else{
        log("out ployon");
    }
    

	m_Dn->clear();
    shape->draw(m_Dn);
    m_Dn->drawDot(currentposition, 3, Color4F(1,0.4,1,0.5));
}



bool CTest::onTouchBegan(Touch* touches, Event *event)
{

   
    currentposition = (touches->getLocation());
    currentposition.x = GRAD_NUMBER(currentposition.x);
    currentposition.y = GRAD_NUMBER(currentposition.y);
    return true;
}

void CTest::onTouchEnded(Touch* touches, Event *event)
{

    flush();
}


void CTest::onTouchMove(Touch* touches, Event *event)
{


}

void CTest::menuCloseCallback(Ref* pSender)
{
	
    //flush();
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
