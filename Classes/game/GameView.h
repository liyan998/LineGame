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
        STATE_INIT,     //��ʼ
        STATE_RUN,      //����
        STATE_WIN,      //ʤ��
        STATE_LOSE      //ʧ�� 
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

    CShowArea*                  m_pShowArea;        //����   

    CMySprite*                  m_pSp;              //��Ҿ���  

    CGamePlayer*                m_pPlayer;          //���ƾ���

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