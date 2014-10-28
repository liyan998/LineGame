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

    m_pSp               = CMySprite::create();
    addChild(m_pSp);

    m_pShowArea         = CShowArea::create(); 
    addChild(m_pShowArea);
    
    m_pShowArea->setPlayer(m_pSp);
    
    //------------------------------------

    setState(STATE_INIT);

    //------------------------------------------

      
}




bool CGameView::onTouchBegan(Touch* touches, Event *event)
{
    //log("CGameView::onTouchBegan<<<<<<<<<<");
    auto local          = touches->getLocation();   
    

    switch (m_state)
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
            m_pSp->setAbsPosition();
        }else{

//             m_pShowArea->addTempPoint(m_pSp->getPosition());
//             m_pShowArea->addTempPoint(local);
            
            m_pSp->setAbsPosition();

            setState(STATE_DRAW);
        }
        log("Selectindex :%d", selectindex);
    }  
    break;
    case STATE_DRAW:
    {
        //test area close
//         int selectindex = m_pShowArea->getTargetIndex(local);
//         m_pShowArea->addTempPoint(local);
//         if (selectindex != SELECTID_NULL)
//         {
//             m_pShowArea->setAreaIndex(1, selectindex);
//             setState(STATE_RUN);
//         }   
//         log("Selectindex :%d", selectindex);
    } 
    break;
    }
    
    return true;
}


void CGameView::onTouchEnded(Touch* touches, Event *event)
{
    auto local = touches->getLocation();
    //log("CGameView::onTouchEnded>>>>>>>>>>>%f, %f", local.x, local.y); 
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
    auto local = touches->getLocation();
    switch (m_state)    
    {
    case STATE_WAIT:        
        m_pShowArea->setPointer(local);
        break;
    case STATE_DRAW:
        m_pShowArea->setPointer(local);
        //auto local = touches->getLocation();
        //m_pShowArea->setPointer(local);
        
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
    //log("spriteRun....%d", count);
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
    //log("random rect Size");
    //TODO random rect Size

}