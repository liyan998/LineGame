#ifndef __SHOWAREA_H__
#define __SHOWAREA_H__

#include "framework/System.h"
#include "Margin.h"

#define SELECTID_NULL -1

class CShowArea : public Sprite
{
public:

    enum State
    {
        STATE_DRAWLINE,             //划线
        STATE_CLOSE                 //闭合状态
    };

    typedef std::vector< Vec2 >::iterator Vec2Iter;

public:

    CREATE_FUNC(CShowArea)

public:

    virtual bool init() override;

    //---------------------------------------------------

    void setPlayerPosiztion(Sprite*);

    void setState(State);                          //

    State getState();

    int getTargetIndex(const  Vec2&);

    void setPointer(const Vec2&);               //设置划线指针位置

    bool isCloseArea();

    void flush();

private:

    DrawNode*                   m_pDrawNode;    //

    std::vector< Vec2 >         m_oAllPoint;    //

    std::vector< Vec2 >         m_oTempPoint;   //

    std::vector< CMargin* >     m_oAllMargin;   //

    int                         m_CurrentIndex; //

    State                       m_State;        //

    Vec2                        m_oMovePointer; //
    
};



#endif//__SHOWAREA_H__