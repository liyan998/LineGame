#include "GameView.h"
#include "util/Math.h"

#include "Rander.h"
#include "Runnable.h"
#include "GameState.h"

#include "ShowArea.h"
#include "MySprite.h"  
#include "Path.h"
#include "Margin.h" 
#include "Game1Player.h"
#include "HelloWorldScene.h"

bool CGameView::init()
{
    Layer::init();

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_DRAGON_SKILL_YUN,
        RES_ANIMA_PLS_DRAGON_SKILL_YUN,
        RES_ANIMA_JSO_DRAGON_SKILL_YUN
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_DRAGON_SKILL_YUNRELEAS,
        RES_ANIMA_PLS_DRAGON_SKILL_YUNRELEAS,
        RES_ANIMA_JSO_DRAGON_SKILL_YUNRELEAS
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_PIPI_HIT,
        RES_ANIMA_PLS_PIPI_HIT,
        RES_ANIMA_JSO_PIPI_HIT
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_COOLKING_HIT,
        RES_ANIMA_PLS_COOLKING_HIT,
        RES_ANIMA_JSO_COOLKING
        );
    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_COOLKING_MAGIC,
        RES_ANIMA_PLS_COOLKING_MAGIC,
        RES_ANIMA_JSO_COOLKING_MAGIC
        );

    //--------------------------------------------------------------------------

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_CAT,
        RES_ANIMA_PLS_CAT,
        RES_ANIMA_JSO_CAT
        );

    //------------------------------------------------------

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_QINCAIDIE,
        RES_ANIMA_PLS_QINCAIDIE,
        RES_ANIMA_JSO_QINCAIDIE
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_DYB,
        RES_ANIMA_PLS_DYB,
        RES_ANIMA_JSO_DYB
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_PIPI_DIE,
        RES_ANIMA_PLS_PIPI_DIE,
        RES_ANIMA_JSO_PIPI_DIE
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_EFFE_DIEREBACK,
        RES_ANIMA_PLS_EFFE_DIEREBACK,
        RES_ANIMA_JSO_EFFE_DIEREBACK
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_PROPERTY,
        RES_ANIMA_PLS_PROPERTY,
        RES_ANIMA_JSO_PROPERTY
        );

    //--------------------------------------------

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_DRAGON,
        RES_ANIMA_PLS_DRAGON,
        RES_ANIMA_JSO_DRAGON
        );

    //-------------------------------------------

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_DRAGON_SKILL_TORNADO,
        RES_ANIMA_PLS_DRAGON_SKILL_TORNADO,
        RES_ANIMA_JSO_DRAGON_SKILL_TORNADO
        );

    //---------------------------------------------

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_COOLKING,
        RES_ANIMA_PLS_COOLKING,
        RES_ANIMA_JSO_COOLKING
        );

    //---------------------------------------------------

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_CAT_SEAL,
        RES_ANIMA_PLS_CAT_SEAL,
        RES_ANIMA_JSO_CAT_SEAL
        );


    return true;
}
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

    m_pPath             = new CPath();
	m_pDrawNode			= DrawNode::create();    	      	
    m_pSp               = CMySprite::create();
    m_pPlayer           = CGamePlayer::create();
    m_pShowArea         = CShowArea::create();
    m_pGameLogic        = CGameLogic::create();
    
    //------------------------------------

	m_pSp->setPath(m_pPath);
    m_pSp->setPlayer(m_pPlayer);
    m_pSp->setShowArea(m_pShowArea);
    m_pSp->setVisible(false);
          
    m_pShowArea->setPath(m_pPath);
    m_pShowArea->setPosition(origin);


    m_pPlayer->m_refSp              = m_pSp;
    m_pPlayer->setVisible(false);

    m_pGameLogic->m_refPath         = m_pPath;
    m_pGameLogic->m_refPlayer       = m_pPlayer;
    m_pGameLogic->m_refShowArea     = m_pShowArea;
    m_pGameLogic->m_refSp           = m_pSp; 
    m_pGameLogic->setAnchorPoint(Vec2::ZERO);
   
    //----------------------------
		
    addChild(m_pShowArea);	
	addChild(m_pSp);
	addChild(m_pDrawNode);
    addChild(m_pGameLogic);
    addChild(m_pPlayer);

    //------------------------------------    	
	
	m_oAllRander.push_back(m_pSp);
    m_oAllRander.push_back(m_pShowArea);
    m_oAllRander.push_back(m_pPath); 
    m_oAllRander.push_back(m_pPlayer);
    
    //----------------------------------------  

    m_oAllRunner.push_back(m_pSp);
    m_oAllRunner.push_back(m_pPlayer);   
	
    //------------------------------------------ 

    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_WIN, this);
    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_TIMEOUT, this);
    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_PLAYERDIE, this);

    setState(STATE_INIT);                         
	schedule(schedule_selector(CGameView::run));
}


void CGameView::actionEvent(int eventid, EventParm data)
{
    switch (eventid)
    {
    case EVENT_WIN:
       h_actionWin(data);
        break;
    case EVENT_TIMEOUT:
    {
                          setState(STATE_LOSE);    
                          gameFinal();    
                          auto gameover = HelloWorld::create();    
                          gameover->setString("Time out you lose!");    
                          addChild(gameover);
    } 
        break;
    case EVENT_PLAYERDIE:
    {
        setState(STATE_LOSE);
        gameFinal();
        auto gameover = HelloWorld::create();
        gameover->setString("GAME OVER!");
        addChild(gameover);
    }   
        break;
    default:
        break;
    }   
}

void CGameView::h_actionWin(EventParm pdadta)
{
    setState(STATE_WIN);
}

void CGameView::setState(int stata)
{
    switch (stata)
    {
    case STATE_INIT:
        log("GAME STATE_INIT");
        schedule(schedule_selector(CGameView::initGame));
        break;      
    case STATE_RUN:
        log("GAME STATE_RUN");

        m_pSp->setVisible(true);
        m_pPlayer->setVisible(true);

        m_oAllRander.push_back(m_pGameLogic);
        m_oAllRunner.push_back(m_pGameLogic);
        break;
    case STATE_WIN:
    {
        log("GAME STATE_WIN");

        gameFinal();

        auto gameover = HelloWorld::create();
        gameover->setString("You Win!");
        addChild(gameover);
    }
        break;
    case STATE_LOSE:
        log("GAME STATE_LOSE");

       
        break;
    }

    this->m_State = stata;
}
          

void CGameView::gameFinal()
{
    m_pGameLogic->released();

    unschedule(schedule_selector(CGameView::run));

    m_oAllRander.clear();
    m_oAllRunner.clear();
    m_pDrawNode->clear();

    m_pSp->released();
    m_pPlayer->released();
    m_pShowArea->released();
}


void CGameView::initGame(float)
{
    //log("random rect Size");
    //TODO random rect Size

    


}

void CGameView::released()
{

}

void CGameView::run(float time)
{
    m_pDrawNode->clear();

    for (int i = 0; i < m_oAllRander.size(); i++)
    {
        m_oAllRander[i]->print(m_pDrawNode);
    }                                           
    //            
    //log("runnable:%d", m_oAllRunner.size());
    for (int i = 0; i < m_oAllRunner.size();i++)
    {
        m_oAllRunner[i]->run(time);
    }
}



bool CGameView::onTouchBegan(Touch* touches, Event *event)
{

    //m_pPlayer->animation_attack();
    if (m_oPointers.size() + 1 > 1)
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

//     if (m_oPointers.size() == 1)
//     {                           
//         const Vec2& endpoint = m_oPointers.begin()->second;
//         log("set Start Point, %f, %f", endpoint.x, endpoint.y);
// 
//         m_pSp->onPressed(endpoint);
//         return;
//     }

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

    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_TIMEOUT, this);
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_PLAYERDIE, this);
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_WIN, this);

    CEventDispatcher::getInstrance()->released();
}