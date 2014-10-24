#include "GameScreen.h"
#include "ui/UiFrom.h"
#include "HelloWorldScene.h"

bool CGameScreen::init()
{
    Scene::init();

    log("CGameScreen init ...");


    //m_oAllScene.insert( MapPair( 1, CREATE_SCENE( CUIFrom ) ));
   // m_oAllScene.insert( MapPair( 2, CREATE_SCENE( HelloWorld )));

    log("CGameScreen inited");
    return true;
}

void CGameScreen::onEnter()
{
    Scene::onEnter();

    log("CGameScreen onEnter ...");
}


void CGameScreen::onExit()
{
    Scene::onExit();

    log("CGameScreen onExit ...");

}