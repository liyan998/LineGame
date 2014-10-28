#ifndef __GAMEVIEW_H__
#define __GAMEVIEW_H__

#include "framework/ui/AGameScene.h"
#include "game/ShowArea.h"
#include "game/MySprite.h"
#include "framework/State.h"




class CGameView : public liyan998::CAGameScene ,public CState
{
public:

    enum State
    {
        STATE_INIT,     //��ʼ
        STATE_WAIT,     //�ȴ�
        STATE_DRAW,     //����
        STATE_RUN       //���� |  
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


    
    //-----------------------------------------------------



private:

    std::vector< Vec2 >         m_oAllPoint;    

    CShowArea*                  m_pShowArea;        //����    

    CMySprite*                  m_pSp;              //��Ҿ���    



    //FIXME--------------------------------
    int count;

};


#endif//__GAMEVIEW_H__