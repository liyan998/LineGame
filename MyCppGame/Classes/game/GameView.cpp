#include "game/GameView.h"
#include "framework/util/Math.h"

void CGameView::onEnter()
{
    Layer::onEnter();
    //----------------------------------------------------
    //FIXME 
    count = 0;

    //----------------------------------------------------

    log("CGameView OnEnter...");

    auto lisnter = EventListenerTouchOneByOne::create();

    //git test

    lisnter->onTouchBegan = CC_CALLBACK_2(CGameView::onTouchBegan, this);
    lisnter->onTouchEnded = CC_CALLBACK_2(CGameView::onTouchEnded, this);
    lisnter->onTouchMoved = CC_CALLBACK_2(CGameView::onTouchMove, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(lisnter, this);

    //--------------------------------------------------------------------

    Size visibleSize    = Director::getInstance()->getVisibleSize();
    auto pSprite             = Sprite::create("HelloWorld.png");
    pSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(pSprite);

    //---------------------------------------------------------------

    m_pShowArea         = CShowArea::create(); 
    addChild(m_pShowArea);

    m_pSp               = CMySprite::create();
    addChild(m_pSp);

       
    
    //------------------------------------

    setState(STATE_INIT);


    //------------------------------------------

      
}




bool CGameView::onTouchBegan(Touch* touches, Event *event)
{
    log("CGameView::onTouchBegan<<<<<<<<<<");
    auto local          = touches->getLocation();   
    int selectindex     = m_pShowArea->getTargetIndex(local);

    switch (m_state)
    {
    case STATE_INIT:
    {   
        unschedule(schedule_selector(CGameView::initGame));
        log("init position random rect Size");
        m_pShowArea->setPlayerPosiztion(m_pSp);
        setState(STATE_WAIT);
    }
        break;
    case STATE_WAIT:
        if (selectindex != SELECTID_NULL)
        {
            //
            log("location position");
            m_pSp->setPosition(local.x, local.y);
        }

        break;
    }
    
    return true;
}


void CGameView::onTouchEnded(Touch* touches, Event *event)
{
    auto local = touches->getLocation();
    log("CGameView::onTouchEnded>>>>>>>>>>>%f, %f", local.x, local.y); 
    switch (m_state)
    {
    case STATE_INIT:
        break;
    case STATE_WAIT:
        break;
    case STATE_DRAW:
        if (m_pShowArea->isCloseArea())
        {
            setState(STATE_RUN);
        }        
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
    
    switch (m_state)    
    {
    case STATE_WAIT:
        setState(STATE_DRAW);
        break;
    case STATE_DRAW:
        auto local = touches->getLocation();
        m_pShowArea->setPointer(local);
        break;
    }   
}



void CGameView::setState(State stata)
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
        this->schedule(schedule_selector(CGameView::spriteRun));
        break;
    }

    this->m_state = stata;
}


CGameView::State CGameView::getState()
{
    return this->m_state;
}


void CGameView::spriteRun(float t)
{
    log("spriteRun....%d", count);
    if (count++ > 100)
    {
        count = 0;
        m_pShowArea->setState(CShowArea::State::STATE_CLOSE);
        unschedule(schedule_selector(CGameView::spriteRun));
        setState(STATE_WAIT);            
    }
}

void CGameView::initGame(float)
{
    log("random rect Size");
    //TODO random rect Size

}