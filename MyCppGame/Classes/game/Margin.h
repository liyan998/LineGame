/************************************************************************/
/* 
功能描述：      边缘
作者：         严黎刚
日期：         2014-10-21

*/
/************************************************************************/
#ifndef __MARGIN_H__
#define __MARGIN_H__

#include "framework/System.h"


#define RA( angle ) angle - 90

#define RECTHEIGHT 15



class CMargin : public Sprite
{
public:
    CREATE_FUNC( CMargin )

public:
    
    virtual bool init();

    void onDraw();

    void setTaget(const Vec2&, const Vec2&); 
  
    Vec2 m_oStart;
    Vec2 m_oTaget;

    DrawNode*                   m_pDrawNode;

    
};

#endif//__MARGIN_H__