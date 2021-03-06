#include "Test.h"
#include "util/Math.h"
#include "util/Util.h"

#include "GameResMacros.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h"

#include "GameElement.h"

#include "cocostudio/CCSGUIReader.h"

using namespace cocostudio;
using namespace liyan998;

bool CTest::init()
{
    Layer::init();

    m_fCount = 0;
    m_iCount = 0;

    cocos2d::SpriteFrameCache* scache = cocos2d::SpriteFrameCache::getInstance();
    cocos2d::TextureCache* tcache = cocos2d::Director::getInstance()->getTextureCache();

    scache->addSpriteFramesWithFile("UI/YXJM_PNG/YXJM.plist", tcache->getTextureForKey("UI/YXJM_PNG/YXJM.png"));
    scache->addSpriteFramesWithFile("UI/Props_Icon_PNG/Props_Icon.plist", tcache->getTextureForKey("UI/Props_Icon_PNG/Props_Icon.png"));


    Vec2 startPosition(100, 100);
    for (int i = 0; i < 2; i++)
    {
        ui::Widget* layer = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("UI/YXJM_daoju_Freezing.json");
        //ui::Button* button = dynamic_cast<ui::Button*>(ui::Helper::seekWidgetByName(layer,"Button_daoju"));
        //layer->setScale(0.5);
        layer->setPosition(Vec2(startPosition.x + i * (layer->getSize().width + 10), startPosition.y
            ));
        addChild(layer);
    }




    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto lisnter = EventListenerTouchOneByOne::create();

    //git test

    lisnter->onTouchBegan = CC_CALLBACK_2(CTest::onTouchBegan, this);
    lisnter->onTouchEnded = CC_CALLBACK_2(CTest::onTouchEnded, this);
    lisnter->onTouchMoved = CC_CALLBACK_2(CTest::onTouchMove,   this);

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


    this->schedule(schedule_selector(CTest::run));
	return true;
}



void CTest::run(float time)
{
    m_fCount += time;
    if (m_fCount >= 1.0f)
    {
       // CGamePlayer* player = (CGamePlayer*)getChildByTag(10000);

       
        m_fCount = 0;
    }

}

void CTest::flush()
{                   
    log("currentPosition:%f, %f", currentposition.x, currentposition.y);
    if (CUtil::hasPointInPloyon(allpoint, currentposition))
    {
        log("in Ployon");
    }
    else
    {
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


   // CAnimationAxis *player = (CAnimationAxis*)getChildByTag(10000);
    
   // CAnimationAxis *player1 = (CAnimationAxis*)getChildByTag(20000);

    
    //player->animation_attack();



    //player->animation_attack();
    //player->getArmature()->getAnimation()->playByIndex(0);
//     Size size = Director::getInstance()->getVisibleSize();
//     player->setPlayerPosition(Vec2(size.width / 2 , size.height / 2));



}
