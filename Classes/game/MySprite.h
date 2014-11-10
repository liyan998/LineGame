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
	

    void setSpStartPosition();							//设置SP起始点坐标

    void setDirectStartPosition(const Vec2& point);		//设置方向检查起始坐标

	void checkDirect(const Vec2& inPos);				//方向检查

	void changeDirect(const Vec2& inPos ,int angle);

	int getAbsDistance();								//得到相对距离

    void run(float tm);									//            

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

    float                   m_fStep;				//步长

    Vec2                    m_oSpStartPosition;     //sp起始位置
    Vec2                    m_oDirectStart;			//方向检查起始点

	Vec2					m_oAbsPosition;			//相对位置起始点
	Vec2					m_oEndPosition;

	int		                m_currentAngle;			//当前角度

    int                     m_iCountRecord;			//

};

#endif//__MYSPRITE_H__