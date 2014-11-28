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

#define MODEL_IN                0                                           //��תģʽ
#define MODEL_OUT               1                                           //һ��ģʽ

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
    public CGameState
{
public:

    enum State
    {
        STATE_INIT,
        STATE_DRAWLINE,                                             //����
        STATE_CLOSE                                                 //�պ�״̬
    };                      

    ////////////////////////////////////////////////////////////////////////   

    typedef std::pair<int, CShape*>                 ShapePair;

    typedef std::map<int, CShape*>::iterator        ShapeIterator;

    //--------------------------------------------------------------

    typedef std::pair<Vec2, unsigned int>           EndPointPair;

    typedef std::map<Vec2, unsigned int>::iterator  EndPointIterator;
                                                                            
    //////////////////////////////////////////////////////////////////////////

public:

    CREATE_FUNC(CShowArea)

public:

    virtual bool init() override;

    virtual void print(DrawNode* dn);                                   //

    virtual void setState(int state);                                   //����״̬

    virtual void released();

    //---------------------------------------------------------------------------------     

    void setPath(CPath* path);

    void setAreaIndex(int index, int areaIndex);                        //������������

    //-------------------------------------------------------------------------------- 

    void clearAreaIndex();                                              //�������

    CMargin* getMargin(int index);                                      //�õ��߽����

    bool isCloseArea();                                                 //�����Ƿ�պ�     
 
    int hasPointInMargin(const Vec2& point);                            //���Ƿ��ڱ߽���

    bool hasPointInArea(const Vec2& point);                             //���Ƿ���������  

    int getNearMargin(const Vec2& point);                               //�õ��õ�����ı�

    int getMode();                                                      //�õ�����ģʽ  

    void getMoveAble(const Vec2& inPoint, std::vector<int>& outDirect); //���ؿ���������

    int getMarginDirect(int direct);                                    //�õ��߽��ϵĿ����߷��� 

    float getArea();                                                    //�ѽ������

    bool hasIncludeMaster();                                            //�Ƿ����BOSS

    void clearSameLineNode(std::vector<Vec2>& outputVec);               //����ͬ����ڵ�    
  
    int getPositionType(const Vec2& inPos);                             //�õ���ǰλ�õ�����

    int getTargetIndex(const  Vec2&);                                   //�õ���ǰ��λ�õı߽�

    bool hasOverLoad(const Vec2& inPoint);

    std::vector< Vec2 > resultArea, addArea;

protected:

    void flushMargin();                                                 //ˢ�±߽���󼯺�   

    void flush();                                                            

    CShape* createShape(int id, std::vector<Vec2>& refAllPoint);        //

    CShape* getShape(const int id);                                     //�õ�ͼ��     

    void setMode(int mode);                                             //���÷���ģʽ

    void checkMarginAvableDirect();                                     //���������������
   
private:

    //-----------------------------------------------------------------------------

    void addPoint(const Vec2& point);                                   //��ӽڵ㵽β��

    void getAllPoint(std::vector<Vec2>& outputVec);                     //�������нڵ�

    unsigned int resetId();                                             //�ڵ���  

    void delPoint(int index);                                           //ɾ�������ڵ�

    void clearPoint();                                                  //������нڵ�

    TPoint* getPoint(int index);                                        //�õ��ڵ�

	TPoint* getPoint(const Vec2& inPosition);                           //�õ��ڵ�

    TPoint* getTempHead(const std::vector<Vec2>& allpoint);

    TPoint* getTempEnd(TPoint* head); 

    void printPoint(TPoint* hp); 

    void selectArea();

    //--------------------------------------------------------------

	void closedLine_Line();

	void closedLine_End();

    void closedEnd_End();

 //////////////////////////////////////////////////////////////////////////

private:

    DrawNode*                       m_pDrawNode;                        //  
    ClippingNode*                   m_pClip;                            //

    TPoint*                         m_pHandle;                          
    std::vector< Vec2 >             m_oAllPoint;
    std::vector< int >              m_oAllMargin;                       //                                                                    

    CPath*                          m_pPath;                            //·��

	int								m_iRorate;							//����
    int                             m_Model;                            //ģʽ

    std::map<Vec2, unsigned int>    m_oAllEndPoint;                     //���ж˵����������

    int                             m_Area[MAX_INDEX];                  //�߽�ID    
    std::map<int, CShape*>          m_oAllShape;                        //ͼ�μ���    

    CGameView*                      m_pGameView;
};                                              


#endif//__SHOWAREA_H__