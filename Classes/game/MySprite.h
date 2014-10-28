#ifndef __MYSPRITE_H__
#define __MYSPRITE_H__

#include "framework/System.h"
#include "framework/State.h"

class CMySprite : public Sprite , public CState
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



    void move(const Vec2& point);

    void pointerMove(const Vec2& pointerVec);

    void setAbsPosition();

    void setPointerStart(const Vec2& point);


private:

    float m_fStep;                              //����

    Vec2 m_AbPosition;                          //���λ��

    std::vector<Vec2>       m_oPath;            //·���ڵ�

    Vec2                    m_oPointerStart;



};

#endif//__MYSPRITE_H__