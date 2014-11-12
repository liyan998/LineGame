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
        STATE_CLOSE,        //
        STATE_BACK          //          
    };

public:

    CREATE_FUNC( CMySprite )

public:

    virtual bool init();             

    virtual void setState(int state);

	virtual void print(DrawNode* dn);

	//----------------------------------------------------

    inline void setPath(CPath* path){ this->m_RefPath = path; };

    inline void setPlayer(CGamePlayer* sp){ this->m_RefPlayer = sp; };

    inline void setShowArea(CShowArea* area){ this->m_RefShowArea = area; };
                                                    
    inline void setPlayerPosition(const Vec2& pos)
    { 
        m_oSpCurrentPos = pos;
        m_RefPlayer->setPlayerPosition(pos);
    };

    //------------------------------------------------------

    void onPressed(const Vec2& pointer);                //     

    void onMove(const Vec2& pointer);                   // 

    void onReleased(const Vec2& pointer);

    //------------------------------------------------------

    void fixPosition(const Vec2& inPos, Vec2& outPos);  //修正位置 

    void playerMove(const Vec2& spPosition);            //精灵移动 

    void setSpStartPosition();							//设置SP起始点坐标

    void setDirectStartPosition(const Vec2& point);		//设置方向检查起始坐标

	void checkDirect(const Vec2& inPos);				//方向检查

	void changeDirect(const Vec2& inPos ,int angle);    //方向改变

    

    bool hasRevceDircet(int direct, int fixangle);      //是否相向运动

	int getAbsDistance();								//得到相对距离

    void run(float tm);									//            

    void addGuide(const Vec2& point);

    void clearGuide();

    void reback();

    void runback();

    void adsorption(const Vec2& inPoint, Vec2& outPoint);//吸附

    void onMoveToDraw(const Vec2& inPoint);
    

private:                                                        

	int getFixAngle(int angle);                 //修正角度

             

private:                                             

    CPath*                  m_RefPath;

    CGamePlayer*            m_RefPlayer;

    CShowArea*              m_RefShowArea;


    std::vector<Vec2>       m_oTPath;            	

    float                   m_fStep;				//步长

    int                     m_curMarginIndex;       //当前选择边
    //-----------------------------------------------------------------

    Vec2                    m_oSpCurrentPos;        //SP当前位置
    Vec2                    m_oSpStartPos;          //sp起始位置

    Vec2                    m_oSpTarget;            //spRebackTarget   

    //手势操作--------------------------------------------------------
	int		                m_currentAngle;			//当前角度 
    Vec2                    m_oDirectStart;			//方向检查起始点 

	Vec2					m_oAbsStartPos;	        //相对位置起始点
	Vec2					m_oAbsEndPos;           //相对位置终点

    int                     m_iCountRecord;			//

};

#endif//__MYSPRITE_H__