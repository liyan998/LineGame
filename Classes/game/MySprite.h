#ifndef __MYSPRITE_H__
#define __MYSPRITE_H__

#include "framework/System.h"

class CMySprite : public Sprite
{

public:

    CREATE_FUNC( CMySprite )

public:

    virtual bool init();

    void move(float radian);

private:

    float m_fStep;  //²½³¤


};

#endif//__MYSPRITE_H__