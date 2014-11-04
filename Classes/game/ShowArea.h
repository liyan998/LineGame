#ifndef __SHOWAREA_H__
#define __SHOWAREA_H__

#include "System.h"
#include "Margin.h"  
#include "Shape.h"
#include "MySprite.h"  

//////////////////////////////////////////////////////////////////////////////////////
                                        

#define SELECTID_NULL   -1                                          //�߽�ѡ��ID NULL

#define MAX_INDEX       2                                           //���ӽڵ��� ��ʼ�� ��ֹ

#define SHAPEID_AREA    11                                          //ͼ��ID �������   
#define SHAPEID_TEMP    12                                          //ͼ��ID ��ʱ����  

#define CLOSETYPE_1     1                                           //�պ�����

//////////////////////////////////////////////////////////////////////////////////////


class CShowArea : 
    public Sprite , 
    public CRander , 
    public CState
{
public:

    enum State
    {
        STATE_DRAWLINE,                                             //����
        STATE_CLOSE                                                 //�պ�״̬
    };

    typedef std::vector< Vec2 >::iterator       Vec2Iter;

    typedef std::pair<int, CShape*>             ShapePair;

    typedef std::map<int, CShape*>::iterator    ShapeIterator;

public:



public:

    CREATE_FUNC(CShowArea)

public:

    virtual bool init() override;

    virtual void print(DrawNode* dn);                               //

    virtual void setState(int state);                               //����״̬

    //---------------------------------------------------------------------------------

    void setPlayer(CMySprite*);

    void setPath(CPath* path);

    void setPlayerPosiztion();

    void setPlayerPosiztion(const Vec2& vec2, int index);  

    void setAreaIndex(int index, int areaIndex);                    //������������     

    int getTargetIndex(const  Vec2&);                               //�õ���ǰ��λ�õı߽�

    CMargin* getMargin(int index);                                  //�õ��߽����      

    bool isCloseArea();                                             //�����Ƿ�պ�

    void runMove(float inv);                                        //ִ���˶�
 
    void clearAreaIndex();                                          //�������
    
    bool hasPointInMargin(const Vec2& point);                       //���Ƿ��ڱ߽���

    bool hasPointInArea(const Vec2& point);                         //���Ƿ���������

    void flushMargin();                                             //ˢ�±߽���󼯺�   

    void flush();

    CShape* createShape(int id, std::vector<Vec2>& refAllPoint);    //

    CShape* getShape(const int id);                                 //�õ�ͼ��

    int*    getMoveAble(const Vec2& pos);                           //���ؿ���������

private:

    void closeArea(int category);                                   //�պ����� 


private:

    DrawNode*                   m_pDrawNode;                        //
    std::vector< Vec2 >         m_oAllPoint;                        //
    std::vector< Vec2 >         m_oTempPoint;                       //
    std::vector< int >          m_oAllMargin;                       //      
                                                                    
    CMySprite*                  m_pPlayer;                          //
    CPath*                      m_pPath;                            //·��
    ClippingNode*               m_pClip;                            //

    int                         m_Area[MAX_INDEX];                  //�߽�ID            
    
    std::map<int, CShape*>      m_oAllShape;                        //ͼ�μ���                   
    
};                                              


#endif//__SHOWAREA_H__