#ifndef __SHOWAREA_H__
#define __SHOWAREA_H__

#include "framework/System.h"
#include "Margin.h"
#include "MySprite.h"
#include "triangulate.h"
#include "Shape.h"
#include "Path.h"


#define SELECTID_NULL   -1

#define MAX_INDEX       2



class CShowArea : public Sprite
{
public:

    enum State
    {
        STATE_DRAWLINE,                         //����
        STATE_CLOSE                             //�պ�״̬
    };

    typedef std::vector< Vec2 >::iterator Vec2Iter;

public:



public:

    CREATE_FUNC(CShowArea)

public:

    virtual bool init() override;

    //---------------------------------------------------

    void setPlayer(CMySprite*);

    void setPath(CPath* path);

    void setPlayerPosiztion();

    void setPlayerPosiztion(const Vec2& vec2, int index);  

    void setAreaIndex(int index, int areaIndex);            //������������

    void setState(State);                                   //����״̬

    State getState();                                       //�õ�״̬

    int getTargetIndex(const  Vec2&);                       //�õ���ǰ��λ�õı߽�

    CMargin* getMargin(int index);                          //�õ��߽����

    void setPointer(const Vec2&);                           //���û���ָ��λ��

    bool isCloseArea();                                     //�����Ƿ�պ�

    void runMove(float inv);                                //ִ���˶�
        
    void addTempPoint(const Vec2&);                         //�����ʱ�ڵ�

    void clearAreaIndex();                                  //�������

    

    bool hasPointInArea(const Vec2& point);                 //���Ƿ���������

    void flushMargin();                                     //ˢ�±߽���󼯺�   

    void flush();

    CShape* createShape(std::vector<Vec2>& refAllPoint);    

    unsigned int getDirect();


    int*    getMoveAble(const Vec2& pos);                   //���ؿ���������

private:

    DrawNode*                   m_pDrawNode;                //
    std::vector< Vec2 >         m_oAllPoint;                //
    std::vector< Vec2 >         m_oTempPoint;               //
    std::vector< int >          m_oAllMargin;               //

   
    State                       m_State;                    //
    Vec2                        m_oMovePointer;             //�ƶ���
    Vec2                        m_oStartPointer;            //��ʼ�ƶ���

    CMySprite*                  m_pPlayer;                  //
    CPath*                      m_pPath;                    //·��
    ClippingNode*               m_pClip;                    //

    int                         m_Area[MAX_INDEX];

    CShape*                     m_pShape;
    std::vector<CShape*>        m_oAllShape;
    
};



#endif//__SHOWAREA_H__