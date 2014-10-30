#ifndef __MYSPRITE_H__
#define __MYSPRITE_H__

#include "framework/System.h"
#include "framework/State.h"
#include "game/Path.h"

#define MAX_ANGLE 4



class CMySprite : public Sprite , public CState, public CRander
{

public:

    enum State
    {
        STATE_STANDER,      //一般模式
        STATE_MOVE,         //移动 == onTouchBegin  离开区域 => draw
        STATE_DRAW,         //划线 == onTouchMove   闭合区域 => run
        STATE_RUN           //运行 == onTouchEnd || closeArea            
    };

public:

    CREATE_FUNC( CMySprite )

public:

    virtual bool init();

    virtual void setState(int state);


	virtual void print(DrawNode* dn);

	//----------------------------------------------------

	void setPath(CPath* path);

    void move(const Vec2& point);

    void pointerMove(const Vec2& pointerVec);

    void setAbsPosition();

    void setPointerStart(const Vec2& point);

private:

	int getFixAngle(int angle);




private:

	CPath* m_RefPath;

    float                   m_fStep;                              //步长

    Vec2                    m_AbPosition;                          //相对位置  

    Vec2                    m_oPointerStart;

	int						m_currentAngle;		//当前角度

    std::vector<int>        m_oAvaMove;         //可行走区域

};

#endif//__MYSPRITE_H__