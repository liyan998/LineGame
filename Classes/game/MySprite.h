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
        STATE_STANDER,      //һ��ģʽ
        STATE_MOVE,         //�ƶ� == onTouchBegin  �뿪���� => draw
        STATE_DRAW,         //���� == onTouchMove   �պ����� => run
        STATE_RUN           //���� == onTouchEnd || closeArea            
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

    float                   m_fStep;                              //����

    Vec2                    m_AbPosition;                          //���λ��  

    Vec2                    m_oPointerStart;

	int						m_currentAngle;		//��ǰ�Ƕ�

    std::vector<int>        m_oAvaMove;         //����������

};

#endif//__MYSPRITE_H__