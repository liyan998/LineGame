#ifndef __MYGAME_H__
#define __MYGAME_H__

#include "framework/AGame.h"
#include "ui/GameScreen.h"
#include "framework/ui/AGameScene.h"

/////////////////////////////////
//
#define SCREEN_WIDTH    640.f
#define SCREEN_HEIGHT   960.f


#define SCENEID_MENU    0x001
#define SCENEID_


class CMyGame : public liyan998::CAGame
{
public:

    virtual void    setState(State);                    //   

    // --------------------------------------------------

    void Init();                                        //
    void Released();                                    //
    void Run();                                         //
    void Stop();                                        //

private:

    CMyGame(){};
        
public:

    static CMyGame* getShareGame();

public:

   

private:

    //EventDispatcher

    //NetServcie

    //DataModel

    //Screen
    CGameScreen*            m_pGameScreen;              //游戏屏幕

private:

    static CMyGame*         m_pGame;                    //共享对象

};



#endif//__MYGAME_H__


