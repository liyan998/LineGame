#ifndef __MYSPRITE_H__
#define __MYSPRITE_H__

#include "System.h"
#include "State.h"
#include "Path.h"

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

    void move(const Vec2& point);

    void pointerMove(const Vec2& pointerVec);

    void setAbsPosition();

    void setPointerStart(const Vec2& point);

private:

	int getFixAngle(int angle);

private:

	CPath*  m_RefPath;

    float   m_fStep;            //����

    Vec2    m_AbPosition;       //���λ��  

    Vec2    m_oPointerStart;

	int		m_currentAngle;		//��ǰ�Ƕ�

    int*    m_pAvaMove;         //����������

};

#endif//__MYSPRITE_H__