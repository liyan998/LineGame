#ifndef __SHOWAREA_H__
#define __SHOWAREA_H__

#include "System.h"
#include "Margin.h"  
#include "Shape.h"
#include "MySprite.h"  

//////////////////////////////////////////////////////////////////////////////////////                                          

#define SELECTID_NULL           -1                                          //�߽�ѡ��ID NULL

#define MAX_INDEX               2                                           //���ӽڵ��� ��ʼ�� ��ֹ

#define SHAPEID_AREA            11                                          //ͼ��ID �������   
#define SHAPEID_TEMP            12                                          //ͼ��ID ��ʱ����  

#define DIRECT_CLOCKWISE        1                                           //�պ�����˳ʱ��
#define DIRECT_ANTICCLOCKWISE   -1                                          //�պ�������ʱ��

#define MODEL_IN                0                                           //�ڲ�ģʽ
#define MODEL_OUT               1                                           //�ⲿģʽ

//////////////////////////////////////////////////////////////////////////////////////

struct TPoint
{    
    Vec2        vec;      

    TPoint*     next; 

    TPoint*     preview;

    int         id;

    bool        isEnd;

    TPoint() :
        next(nullptr), 
        preview(nullptr),
        isEnd(false),
        id(-1)
    {};

    ~TPoint(){ preview = nullptr; next = nullptr; };
};


//////////////////////////////////////////////////////////////////////////


class CShowArea : 
    public Sprite , 
    public CRander , 
    public CState
{
public:

    enum State
    {
        STATE_INIT,
        STATE_DRAWLINE,                                             //����
        STATE_CLOSE                                                 //�պ�״̬
    };

    typedef std::vector< Vec2 >::iterator       Vec2Iter;

    typedef std::pair<int, CShape*>             ShapePair;

    typedef std::map<int, CShape*>::iterator    ShapeIterator;

    //////////////////////////////////////////////////////////////////////////

public:

    CREATE_FUNC(CShowArea)

public:

    virtual bool init() override;

    virtual void print(DrawNode* dn);                               //

    virtual void setState(int state);                               //����״̬

    //---------------------------------------------------------------------------------     

    void setPath(CPath* path); 

    void setAreaIndex(int index, int areaIndex);                    //������������     

    //--------------------------------------------------------------------------------

    int getTargetIndex(const  Vec2&);                               //�õ���ǰ��λ�õı߽�

    CMargin* getMargin(int index);                                  //�õ��߽����   

    bool isCloseArea();                                             //�����Ƿ�պ�  
 
    void clearAreaIndex();                                          //�������
    
    bool hasPointInMargin(const Vec2& point);                       //���Ƿ��ڱ߽���

    bool hasPointInArea(const Vec2& point);                         //���Ƿ���������   

    int getMode();                                                  //�õ�����ģʽ

protected:

    void flushMargin();                                             //ˢ�±߽���󼯺�   

    void flush();                                                            

    CShape* createShape(int id, std::vector<Vec2>& refAllPoint);    //

    CShape* getShape(const int id);                                 //�õ�ͼ��

    int*    getMoveAble(const Vec2& pos);                           //���ؿ���������

    void setMode(int mode);                                         //���÷���ģʽ    
   

private:

    //-----------------------------------------------------------------------------

    void addPoint(const Vec2& point);                               //��ӽڵ㵽β��

    void getAllPoint(std::vector<Vec2>& outputVec);                 //�������нڵ�

    unsigned int resetId();                                         //�ڵ���
                                                                            
    void delPoint(int start, int end, int category);                //ɾ���ڵ�

    void delPoint(int index);                                       //ɾ�������ڵ�

    void insert(std::vector<Vec2>& allpint, int start, int end);    //����ڵ�

    void clearPoint();                                              //������нڵ�

    TPoint* getPoint(int index);                                    //�õ��ڵ�

    TPoint* getTempHead(const std::vector<Vec2>& allpoint);

    TPoint* getTempEnd(TPoint* head);        

    void printPoint(TPoint* hp);

 //////////////////////////////////////////////////////////////////////////

private:

    DrawNode*                   m_pDrawNode;                        //  

    TPoint*                     m_pHandle;                          

    std::vector<Vec2>           m_oAllPoint;
    std::vector<Vec2>           m_oTempPoint;
    std::vector< int >          m_oAllMargin;                       //
                                                                    

    CPath*                      m_pPath;                            //·��
    ClippingNode*               m_pClip;                            //

    int                         m_Area[MAX_INDEX];                  //�߽�ID            
    
    std::map<int, CShape*>      m_oAllShape;                        //ͼ�μ���  

    int                         m_Model;                            //ģʽ
    
};                                              


#endif//__SHOWAREA_H__