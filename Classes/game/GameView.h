#ifndef __GAMEVIEW_H__
#define __GAMEVIEW_H__

#include "framework/ui/AGameScene.h"

#include "Rander.h"
#include "State.h"
#include "ShowArea.h"
#include "MySprite.h"  
#include "Path.h"
#include "Margin.h" 


class CGameView : 
    public liyan998::CAGameScene ,
    public CState
{
public:

    enum State
    {
        STATE_INIT,     //初始
        STATE_WAIT,     //等待
        STATE_DRAW,     //划线
        STATE_RUN       //行走 
    };
       
public:

    CREATE_FUNC( CGameView )

public:
    
    virtual void onEnter() override;

    bool onTouchBegan(Touch* touches, Event *event);

    void onTouchEnded(Touch* touches, Event *event);

    void onTouchMove(Touch* touches, Event *event);

    //---------------------------------------------

    virtual void setState(int state);

    void initGame(float);

    void drawLine();

    void spriteRun(float);

	void run(float time);             
    
    //-----------------------------------------------------   

private:                                                       

    CShowArea*                  m_pShowArea;        //区域    

    CMySprite*                  m_pSp;              //玩家精灵    

	CPath*						m_pPath;

	DrawNode*					m_pDrawNode;		//

	std::vector< CRander* >		m_oAllRander;   	


    //FIXME--------------------------------
    int count;                          
};


#endif//__GAMEVIEW_H__