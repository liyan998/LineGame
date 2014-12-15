#ifndef __GAMEVIEW_H__
#define __GAMEVIEW_H__



#include "System.h" 
#include "GameLogic.h"
#include "EventSystem.h"


class CRander;
class CRunnable;
class CGameState;

class CMySprite;
class CGamePlayer;
class CShowArea;
class CPath;
class CMargin;  


class CGameView : 
    //public liyan998::CAGameScene ,
    public Layer,
    public CGameState,
    public CEventHandler
{

public:

    typedef std::pair<int, Vec2> PointPari;

    typedef std::map<int, Vec2>::iterator PointIter;

public:

    enum State
    {
        STATE_INIT,     //初始
        STATE_RUN,      //运行
        STATE_WIN,      //胜利
        STATE_LOSE      //失败 
    };
       
public:

    CREATE_FUNC( CGameView )

public:
    
    virtual void onEnter() override;

    virtual void onExit() override;

    bool onTouchBegan(Touch* touches, Event *event);

    void onTouchEnded(Touch* touches, Event *event);

    void onTouchMove(Touch* touches, Event *event);

    
    virtual void released();

    virtual void actionEvent(int eventid, EventParm data);

    //---------------------------------------------   -----

    void menuCloseCallback(Ref* ref);

    virtual void setState(int state);

    void initGame(float); 

	void run(float time);                                   
    
    //----------------------------------------------------- 

    void h_actionWin(EventParm pdadta);

private:                                                       

    CShowArea*                  m_pShowArea;        //区域   

    CMySprite*                  m_pSp;              //玩家精灵  

    CGamePlayer*                m_pPlayer;          //控制精灵

	CPath*						m_pPath;

	DrawNode*					m_pDrawNode;		//

	std::vector< CRander* >		m_oAllRander;   

    std::vector< CRunnable* >   m_oAllRunner;

    std::map< int , Vec2 >      m_oPointers;

    CGameLogic*                 m_pGameLogic;

    //FIXME--------------------------------
    int count;                          
};


#endif//__GAMEVIEW_H__