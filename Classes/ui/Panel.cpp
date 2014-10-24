/************************************************************************/
/*



*/
/************************************************************************/

#include "Panel.h"

//
//
//
bool CPanel::init()
{   
    Layer::init();    
   
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("khh/HWYJ.plist", "khh/HWYJ.png");

    //--------------------------------------------------------

    TUIParm t_panelbg[] = 
    { 
        { "IMG_ditu2.png",          Point(.5f, 0),   Point(visibleSize.width / 2 , 30 ), 0x10001 },      
        { "IMG_huweixinxi.png",     Point(.5f, .5f), Point(visibleSize.width / 2, visibleSize.height / 2 + 30), 0x10005 },     
        { "TMG_huweitujian.png",    Point(0.5f, .5f),Point(visibleSize.width / 2, visibleSize.height / 2 + 230), 0x10009}
    };

    int uiSize = sizeof(t_panelbg) / sizeof(TUIParm);
    for (int i = 0; i < uiSize; i++)
    {
        addUIElement(t_panelbg[i]);
    }

    //----------------------------------------

    auto pBigIcon = Sprite::createWithSpriteFrameName("IMG_xshouling1.png");
    pBigIcon->setPosition(Point(visibleSize.width / 2 - 150, visibleSize.height / 2));
    pBigIcon->setScale(1.5f);
    addChild(pBigIcon);       
   
    //-----------------------------------------------

    Sprite* pButton1 = Sprite::createWithSpriteFrameName("IMG_fanhui.png");
    Sprite* pButton2 = Sprite::createWithSpriteFrameName("IMG_fanhui3.png");
    Sprite* pButton3 = Sprite::createWithSpriteFrameName("IMG_fanhui3.png");

    //---------------------------------------------------
    //FIXME 触摸事件问题
//     auto listener1 = EventListenerTouchOneByOne::create();
// 
//     listener1->setSwallowTouches(true);
//     listener1->onTouchBegan = [](Touch* touch, Event* event){
//         auto target = static_cast<Sprite*>(event->getCurrentTarget());
//         Director::getInstance()->end();
//         return true;
//     }; 
//     _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, pButton1); 

    //---------------------------------------------------------------------

    auto closeItem = MenuItemSprite::create(
        pButton1,
        pButton2,
        pButton3,
        CC_CALLBACK_1(CPanel::menuCloseCallback, this)       
        );
    closeItem->setPosition(Point(50, visibleSize.height / 2 + 240));


    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu, 1);

    //---------------------------------------------------

       
    int listSx = 120, listSy = 100, inval = 20;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            auto pSpriteIcon = Sprite::createWithSpriteFrameName("IMG_xshouling1.png");
            auto pSpriteItem = Sprite::createWithSpriteFrameName("IMG_xxbj.png");

            int listiconW = pSpriteIcon->getContentSize().width;
            int listiconH = pSpriteIcon->getContentSize().height;
            int x = listSx + (listiconW + inval) * j;
            int y = listSy + (listiconH + inval) * i;

            // pSpriteItem->setScale(0.8f);

            CUIElement* pElement = CUIElement::create();
            pElement->setIcon(pSpriteIcon);
            pElement->setLab(pSpriteItem);
            pElement->setScale(0.8f);
            pElement->setPosition(Point(x, y));           

            menu->addChild(pElement);
        }
    }
  

    log("CPanel init");
    return true;
}


void CPanel::onEnter()
{
    Layer::onEnter();
    log("CPanel onEneter");   
}


void CPanel::onExit()
{
    Layer::onExit();
    log("CPanel onExit");

}


//
//
//
void CPanel::addUIElement(const TUIParm& uiPos)
{
    auto pPanelBg = Sprite::createWithSpriteFrameName(uiPos.resName);
    pPanelBg->setAnchorPoint(uiPos.ancPoint);
    pPanelBg->setPosition(uiPos.posPoint);
    addChild(pPanelBg);
}

void CPanel::menuCloseCallback(Ref* pSender)
{
    log("close window");
}


