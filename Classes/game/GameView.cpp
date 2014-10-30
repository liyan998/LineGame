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

    lisnter->onTouchBegan = CC_CALLBACK_2(CGameView::onTouchBegan, this);
    lisnter->onTouchEnded = CC_CALLBACK_2(CGameView::onTouchEnded, this);
    lisnter->onTouchMoved = CC_CALLBACK_2(CGameView::onTouchMove, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(lisnter, this);

    //--------------------------------------------------------------------
	m_pDrawNode			= DrawNode::create();

	m_pPath				= new CPath();
	
    m_pSp               = CMySprite::create();
    m_pShowArea         = CShowArea::create();    
    
	m_pSp->setPath(m_pPath);
    m_pShowArea->setPlayer(m_pSp);
    m_pShowArea->setPath(m_pPath);
		
    addChild(m_pShowArea);	
	addChild(m_pSp);
	addChild(m_pDrawNode);
    //------------------------------------
	
	m_oAllRander.push_back(m_pPath);
	m_oAllRander.push_back(m_pSp);

    setState(STATE_INIT);
	
    //------------------------------------------  

	schedule(schedule_selector(CGameView::run));
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
           
        }else{
//             m_pShowArea->addTempPoint(m_pSp->getPosition());
//             m_pShowArea->addTempPoint(local);            
            //m_pSp->setAbsPosition();
            //setState(STATE_DRAW);
        } 
        m_pSp->setState(CMySprite::STATE_DRAW);
        m_pSp->setPointerStart(local);
        m_pSp->setAbsPosition();
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
       // m_pShowArea->setPointer(local);
        //移动精灵、如果不在区域内 draw

        m_pSp->move(local);
        
        if (!m_pShowArea->hasPointInArea(pos))
        {
            

//             if (margin != NULL)
//             {
//                 m_pPath->addPoint(liyan998::CMath::getFootPoint(margin->m_oStart, margin->m_oTaget, pos));
//             }
//             else{
//                 m_pPath->addPoint(pos);
// 
//             }
           
            m_pShowArea->setAreaIndex(0, selectindex);
            setState(STATE_DRAW);
        }
        break;
    case STATE_DRAW:
        //m_pShowArea->setPointer(local);
        //auto local = touches->getLocation();
        //m_pShowArea->setPointer(local);

        m_pSp->move(local);     
        if (m_pShowArea->hasPointInArea(pos))
        {            
            if (margin != NULL)
            {
                m_pPath->addPoint(liyan998::CMath::getFootPoint(margin->m_oStart, margin->m_oTaget, pos));
            }
            else{
                m_pPath->addPoint(pos);
            }
            m_pSp->setState(CMySprite::STATE_MOVE);          
            m_pShowArea->setAreaIndex(1, selectindex);
            setState(STATE_RUN);
        }
        //收集节点
        
        break;
    }   
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

	for (int i = 0;i < m_oAllRander.size();i++)
	{
		m_oAllRander[i]->print(m_pDrawNode);
	}

}