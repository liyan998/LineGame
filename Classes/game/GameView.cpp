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

    //FIXME 重命名
    m_pShowArea->setPlayer(m_pSp);
    m_pShowArea->setPath(m_pPath);
		
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
    case STATE_DRAW:
        log("STATE_DRAW");
        break;
    case STATE_WAIT:
        log("STATE_WAIT");
        break;
    case STATE_RUN:
        log("STATE_RUN");
        m_pPlayer->moveToPath(m_pPath->m_oAllPoint);
        this->schedule(schedule_selector(CGameView::spriteRun));
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
        setState(STATE_WAIT);
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
    //log("CGameView::onTouchBegan<<<<<<<<<<");
    auto local          = touches->getLocation();    

    switch (m_State)
    {
    case STATE_INIT:
    {   
        unschedule(schedule_selector(CGameView::initGame));
        log("init position random rect Size");
        m_pShowArea->setPlayerPosiztion();
        setState(STATE_WAIT);    
    } 
    break;
    case STATE_WAIT:
    {
        int selectindex = m_pShowArea->getTargetIndex(local);
        if (selectindex != SELECTID_NULL)
        {
            //
            log("location position");
            m_pShowArea->setAreaIndex(0, selectindex);
            m_pShowArea->setPlayerPosiztion(local, selectindex);

        } 
        m_pSp->setState(CMySprite::STATE_MOVE);
        m_pSp->setAbsPosition();       
        m_pSp->setPointerStart(local);
        
        log("Selectindex :%d", selectindex);
    }  
    break;
    case STATE_DRAW:
    {

    } 
    break;
    }
    
    return true;
}


void CGameView::onTouchEnded(Touch* touches, Event *event)
{
    auto local = touches->getLocation();
    //log("CGameView::onTouchEnded>>>>>>>>>>>%f, %f", local.x, local.y); 
    switch (m_State)
    {
    case STATE_INIT:
        break;
    case STATE_WAIT:  
        m_pSp->setState(CMySprite::STATE_STANDER);
		break;
    case STATE_DRAW:        
        setState(STATE_RUN);            
        break;
    case STATE_RUN:
        break;
    default:
        break;
    }

}                                              


void CGameView::onTouchMove(Touch* touches, Event *event)
{
    //log("CGameView::onTouchMove-------------");
    auto local          = touches->getLocation();

    const Vec2& pos     = m_pSp->getPosition();
    int selectindex     = m_pShowArea->getTargetIndex(pos);
    CMargin* margin     = m_pShowArea->getMargin(selectindex);

    switch (m_State)
    {
    case STATE_WAIT:              
        if (!m_pShowArea->hasPointInArea(pos))
        {            
            m_pSp->setState(CMySprite::STATE_DRAW);
            m_pShowArea->setAreaIndex(0, selectindex);
            setState(STATE_DRAW);
            return;
        }
        m_pSp->move(local);
        break;
    case STATE_DRAW:   
        if (m_pShowArea->hasPointInArea(pos))
        {       
            if (margin != nullptr)
            {
                const Vec2 & v = liyan998::CMath::getFootPoint(margin->m_oStart, margin->m_oTaget, m_pPath->m_oAllPoint[m_pPath->m_oAllPoint.size() - 1]);

                selectindex = m_pShowArea->getTargetIndex(v);
                m_pSp->setPosition(v);
                m_pPath->addPoint(v); 
                
            }else{
                 //FIXME 移动速度过快会造成无法得到边界信息    
                log("FIXME");
            }

            m_pShowArea->setAreaIndex(1, selectindex);
            setState(STATE_RUN);
            return;
        }                             

        m_pSp->move(local);        
        break;
    }  
}


void CGameView::menuCloseCallback(Ref* ref)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
    return;
#endif

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
}