#ifndef __MYSPRITE_H__
#define __MYSPRITE_H__

#include "framework/System.h"

class CMySprite : public Sprite
{

public:

    enum State
    {

        STATE_STANDER,
        STATE_MOVE,

    };

public:

    CREATE_FUNC( CMySprite )

public:

    virtual bool init();

    void move(float radian);

    void pointerMove(Vec2& pointerVec);

    void setAbsPosition();


private:

    float m_fStep;          //步长

    Vec2 m_AbPosition;      //相对位置



};

#endif//__MYSPRITE_H__