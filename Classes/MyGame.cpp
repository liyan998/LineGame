/************************************************************************/
/* 



*/
/************************************************************************/

#include "MyGame.h"

#include "HelloWorldScene.h"
#include "ui/UiFrom.h"
#include "game/GameView.h"
#include "game/Test.h"

//////////////////////////////////////////////////////////////////////////
//
CMyGame* CMyGame::m_pGame = NULL;



//////////////////////////////////////////////////////////////////////////
//
CMyGame* CMyGame::getShareGame()
{
    if (!m_pGame)
    {
        m_pGame = new CMyGame();
    }

    return m_pGame;
}

void CMyGame::Init()
{
    log("MyGame Init ...");

    //////////////////////////////////////////////////////////////////////////
    //DataModel


    //////////////////////////////////////////////////////////////////////////
    //Event
    
    //////////////////////////////////////////////////////////////////////////
    //Net   

    //////////////////////////////////////////////////////////////////////////
    //UiContext

   
    
    m_pGameScreen = CGameScreen::create();

    m_pGameScreen->InitScene(liyan998::MapPair(31, CREATE_SCENE( CGameView )));
    m_pGameScreen->InitScene(liyan998::MapPair(11, CREATE_SCENE( HelloWorld )));
    m_pGameScreen->InitScene(liyan998::MapPair(12, CREATE_SCENE( CUIFrom )));
    m_pGameScreen->InitScene(liyan998::MapPair(13, CREATE_SCENE( CTest )));

    auto director = Director::getInstance();  
    director->runWithScene(m_pGameScreen);

    m_pGameScreen->SetScene( 13 );

    log("MyGame Init finished");
}

//
//
//
//
void CMyGame::Stop()
{
    log("MyGame Stop ...");    
}


void CMyGame::Run()
{
    log("MyGame Run ...");
}

void CMyGame::Released()
{
    //////////////////////////////////////////////////////////////////////////
    //UiContext

    //////////////////////////////////////////////////////////////////////////
    //Net

    //////////////////////////////////////////////////////////////////////////
    //Event

    //////////////////////////////////////////////////////////////////////////
    //DataModel
    
    Director::getInstance()->end();
    log("MyGame Released");
}

void CMyGame::setState(State state)
{
    switch (state)
    {
    case CAGame::STATE_INIT:
    {
        Init();
    }
        break;
    case CAGame::STATE_RUN:                         
    {
        Run();
    }
        break;
    case CAGame::STATE_STOP:
    {
        Stop();
    }
        break;
    }
    this->m_State = state;
}
