#ifndef __SHOWAREA_H__
#define __SHOWAREA_H__

#include "framework/System.h"
#include "Margin.h"
#include "MySprite.h"

#define SELECTID_NULL -1


class CShowArea : public Sprite
{
public:

    enum State
    {
        STATE_DRAWLINE,             //����
        STATE_CLOSE                 //�պ�״̬
    };

    typedef std::vector< Vec2 >::iterator Vec2Iter;

public:

    CREATE_FUNC(CShowArea)

public:

    virtual bool init() override;

    //---------------------------------------------------

    void setPlayerPosiztion(Sprite*);

    void setPlayer(CMySprite*);

    void setState(State);                          //

    State getState();

    int getTargetIndex(const  Vec2&);           //�õ���ǰ��λ�õı߽�

    void setPointer(const Vec2&);               //���û���ָ��λ��

    bool isCloseArea();                         //�����Ƿ�պ�

    void runMove(float inv);                    //ִ���˶�

    void addTempPoint(const Vec2&);                     //�����ʱ�ڵ�

    void flush();

private:

    DrawNode*                   m_pDrawNode;    //

    std::vector< Vec2 >         m_oAllPoint;    //

    std::vector< Vec2 >         m_oTempPoint;   //

    std::vector< CMargin* >     m_oAllMargin;   //

    int                         m_CurrentIndex; //

    State                       m_State;        //

    Vec2                        m_oMovePointer; //�ƶ���
    Vec2                        m_oStartPointer;//��ʼ�ƶ���

    CMySprite*                  m_pPlayer;
    
};



#endif//__SHOWAREA_H__