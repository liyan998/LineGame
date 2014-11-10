#ifndef __MYSPRITE_H__
#define __MYSPRITE_H__

#include "System.h"

#include "State.h"
#include "Path.h"
#include "Game1Player.h"


class CShowArea;

#define MAX_ANGLE 4

/************************************************************************/
/* 



*/
/************************************************************************/
class CMySprite : 
public Sprite,
public CState, 
public CRander
{          

public:         

    enum State
    {
        STATE_INIT,         //
        STATE_STANDER,      //
        STATE_MOVE,         //
        STATE_DRAW,         //
        STATE_RUN           //          
    };

public:

    CREATE_FUNC( CMySprite )

public:

    virtual bool init();             

    virtual void setState(int state);

	virtual void print(DrawNode* dn);

	//----------------------------------------------------

	void setPath(CPath* path);

    void setPlayer(CGamePlayer* sp);

    void setShowArea(CShowArea* area);
                                                    
    void setPlayerPosition(const Vec2& pos);  

    //------------------------------------------------------

    void onPressed(const Vec2& vec2);             //

    void onMove(const Vec2& point);               // 

    //------------------------------------------------------

    void fixPosition(const Vec2& inPos, Vec2& outPos);



    void setAbsPosition();                      //设置相对坐标

    void setPointerStart(const Vec2& point);    //设置相对起始坐标

    void run(float tm);                         //            

    void addGuide(const Vec2& point);

    void clearGuide();

   

private:                                                        

	int getFixAngle(int angle);                 //修正角度

    void spriteMove();                          //精灵移动          

private:                                             

    CPath*                  m_RefPath;

    CGamePlayer*            m_RefPlayer;

    CShowArea*              m_RefShowArea;


    std::vector<Vec2>       m_oTPath;            	

    float                   m_fStep;            //步长

    Vec2                    m_AbPosition;       //相对位置  

    Vec2                    m_oPointerStart;

	int		                m_currentAngle;		//当前角度

    int                     m_iCountRecord;     //记录相对节点的次数

};

#endif//__MYSPRITE_H__