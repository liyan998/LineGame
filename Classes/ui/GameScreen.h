/************************************************************************/
/* 

作者:     严黎刚
日期:     2014-10-20

*/
/************************************************************************/
#ifndef __GAMESCREEN_H__
#define __GAMESCREEN_H__

#include "framework/ui/AGameScreen.h"

class CGameScreen : public liyan998::CAGameScreen
{

public:

    CREATE_FUNC( CGameScreen )

public:

    virtual bool init() override;                                           //
    virtual void onEnter() override;                                        //
    virtual void onExit() override;                                         //

};
#endif//__GAMESCREEN_H__