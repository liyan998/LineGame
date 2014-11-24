/************************************************************************/
/* 
功能描述：      边缘
作者：         严黎刚
日期：         2014-10-21

*/
/************************************************************************/
#ifndef __MARGIN_H__
#define __MARGIN_H__

#include "System.h"


#define RA( angle ) angle - 90

#define RECTHEIGHT 15



class CMargin : public Sprite
{
public:
    CREATE_FUNC( CMargin )

public:

    CMargin():m_pDrawNode(nullptr){};
    
    virtual bool init();

    void onDraw();

    void setTaget(const Vec2&, const Vec2&);  

    void getAvableDirect(const std::vector<Vec2>& inAllPoint, 
        std::map<Vec2, unsigned int>& outAllEndPoint);

    void setAvableDirect(int direct);

private:

    void addPointToMap(const Vec2& inPoint,
        std::map<Vec2, unsigned int>& outAllEndPoint);

public:
  
    Vec2 m_oStart;
    Vec2 m_oTaget;

    DrawNode*                   m_pDrawNode;

    int                         m_Angle;

    int                         m_iMarginAvable;                  //与模式依赖边界可行走方向
    int                         m_iAvable;                        //可行走方向

    
    
};

#endif//__MARGIN_H__