#ifndef __SHOWAREA_H__
#define __SHOWAREA_H__

#include "framework/System.h"
#include "Margin.h"
#include "MySprite.h"
#include "triangulate.h"




#define SELECTID_NULL   -1

#define MAX_INDEX       2


class CShowArea : public Sprite
{
public:

    enum State
    {
        STATE_DRAWLINE,                         //划线
        STATE_CLOSE                             //闭合状态
    };

    typedef std::vector< Vec2 >::iterator Vec2Iter;

public:

    CREATE_FUNC(CShowArea)

public:

    virtual bool init() override;

    //---------------------------------------------------

    void setPlayerPosiztion(Sprite*);

    void setPlayer(CMySprite*);

    void setState(State);                       //

    State getState();

    int getTargetIndex(const  Vec2&);           //得到当前点位置的边界

    void setPointer(const Vec2&);               //设置划线指针位置

    bool isCloseArea();                         //区域是否闭合

    void runMove(float inv);                    //执行运动

    void addTempPoint(const Vec2&);             //添加临时节点

    void clearAreaIndex();                      //清除区间

    void setAreaIndex(int index, int areaIndex);//设置区间索引

    void flushMargin();

    void flush();


private:

    DrawNode*                   m_pDrawNode;    //
    std::vector< Vec2 >         m_oAllPoint;    //
    std::vector< Vec2 >         m_oTempPoint;   //
    std::vector< int >          m_oAllMargin;   //

   
    State                       m_State;        //
    Vec2                        m_oMovePointer; //移动点
    Vec2                        m_oStartPointer;//起始移动点

    CMySprite*                  m_pPlayer;      //
    ClippingNode*               m_pClip;        //

    int                         m_Area[MAX_INDEX];
    
};



#endif//__SHOWAREA_H__