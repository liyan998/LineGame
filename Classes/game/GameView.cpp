#include "GameView.h"
#include "util/Math.h"


void CGameView::onEnter()
{
    Layer::onEnter();
    //----------------------------------------------------
    //FIXME 
    count = 0;
    

    Size visibleSize    = Director::getInstance()->getVisibleSize();
    Vec2 origin         = Director::getInstance()->getVisibleOrigin();

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(CGameView::menuCloseCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
        origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //----------------------------------------------------

    log("CGameView OnEnter...");

    auto lisnter = EventListenerTouchOneByOne::create();

    lisnter->onTouchBegan = CC_CALLBACK_2(CGameView::onTouchBegan, this);
    lisnter->onTouchEnded = CC_CALLBACK_2(CGameView::onTouchEnded, this);
    lisnter->onTouchMoved = CC_CALLBACK_2(CGameView::onTouchMove, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(lisnter, this);

    //--------------------------------------------------------------------
    m_pPath = new CPath();

	m_pDrawNode			= DrawNode::create();    	      	
    m_pSp               = CMySprite::create();
    m_pPlayer           = CGamePlayer::create();
    m_pShowArea         = CShowArea::create();    
    
	m_pSp->setPath(m_pPath);
    m_pSp->setPlayer(m_pPlayer);
    m_pSp->setShowArea(m_pShowArea);
          
    m_pShowArea->setPath(m_pPath);
    m_pShowArea->setPosition(origin);

		
    addChild(m_pShowArea);	
	addChild(m_pSp);
	addChild(m_pDrawNode);
    addChild(m_pPlayer);
    //------------------------------------    	
	
	m_oAllRander.push_back(m_pSp);
    m_oAllRander.push_back(m_pShowArea);
    m_oAllRander.push_back(m_pPath);

    setState(STATE_INIT);
	
    //------------------------------------------  

	schedule(schedule_selector(CGameView::run));

}

void CGameView::setState(int stata)
{
    switch (stata)
    {
    case STATE_INIT:
        log("STATE_INIT");
        schedule(schedule_selector(CGameView::initGame));
        break;      
    case STATE_RUN:
        log("STATE_RUN");        
        break;
    }

    this->m_State = stata;
}
          

void CGameView::spriteRun(float t)
{
    //log("spriteRun....%d", count);
    if (count++ > 100)
    {
        count = 0;
        m_pShowArea->setState(CShowArea::State::STATE_CLOSE);
        m_pSp->setState(CMySprite::STATE_STANDER);
        m_pPath->clearPoint();

        unschedule(schedule_selector(CGameView::spriteRun));
        
    }
}


void CGameView::initGame(float)
{
    //log("random rect Size");
    //TODO random rect Size


}


void CGameView::run(float time)
{
    m_pDrawNode->clear();

    for (int i = 0; i < m_oAllRander.size(); i++)
    {
        m_oAllRander[i]->print(m_pDrawNode);
    }
}



bool CGameView::onTouchBegan(Touch* touches, Event *event)
{

    if (m_oPointers.size() + 1 > 2)
    {                   
        return false;
    }
                                       
    auto local          = touches->getLocation();    
    log("CGameView::onTouchBegan<<<<<<<<<< %d", m_oPointers.size());
    log("id:%d, point:%f, %f", touches->getID(), local.x, local.y );
                                                        
    m_oPointers.insert(PointPari(touches->getID(), local));

    switch (m_State)
    {
    case STATE_INIT:
    {   
        unschedule(schedule_selector(CGameView::initGame));
        log("init position random rect Size");
     
        m_pSp->setState(CMySprite::STATE_INIT);
    } 
    break;
    case STATE_RUN:      
        m_pSp->onPressed(local);                         
        break;   
    }
    
    return true;
}


void CGameView::onTouchEnded(Touch* touches, Event *event)
{
    PointIter pinter = m_oPointers.find(touches->getID());

    if (pinter != m_oPointers.end())
    {
        m_oPointers.erase(pinter);
    } 
    else
    {
        log("not find! id");
    }

    if (m_oPointers.size() == 1)
    {                           
        const Vec2& endpoint = m_oPointers.begin()->second;
        log("set Start Point, %f, %f", endpoint.x, endpoint.y);

        m_pSp->onPressed(endpoint);
        return;
    }

    auto local = touches->getLocation();
    //log("CGameView::onTouchEnded>>>>>>>>>>> %d", m_oPointers.size());
    //log("CGameView::onTouchEnded>>>>>>>>>>>%f, %f", local.x, local.y); 
    switch (m_State)
    {
    case STATE_INIT:
        setState(STATE_RUN);
        break;
    case STATE_RUN:
        m_pSp->onReleased(local);         
        break;
    }

}                                              


void CGameView::onTouchMove(Touch* touches, Event *event)
{
    auto local = touches->getLocation(); 
                               
    PointIter iter = m_oPointers.find(touches->getID()); 
    if (iter != m_oPointers.end())
    {
        iter->second = local;
    }

    //log("CGameView::onTouchMove-------------%d", m_oPointers.size());
    if (m_oPointers.size() > 1)
    {
        return;
    }

    switch (m_State)
    {                
    case STATE_RUN:           
        m_pSp->onMove(local); 
        break;
    }  
}


void CGameView::menuCloseCallback(Ref* ref)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
    return;
#endif

    log("exit~~~~~~!");
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif


}

void CGameView::onExit()
{
    Layer::onExit();

	m_oAllRander.clear();

    this->removeAllChildren();
  
    delete m_pPath;
    m_pPath = nullptr;
}