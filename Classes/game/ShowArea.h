#ifndef __SHOWAREA_H__
#define __SHOWAREA_H__

#include "System.h"
#include "Margin.h"  
#include "Shape.h"
#include "MySprite.h"  




//////////////////////////////////////////////////////////////////////////////////////                                          

#define SELECTID_NULL           -1                                          //边界选择ID NULL

#define MAX_INDEX               2                                           //连接节点数 起始， 终止

#define SHAPEID_AREA            11                                          //图形ID 封闭区域   
#define SHAPEID_TEMP            12                                          //图形ID 临时区域

#define MODEL_IN                0                                           //反转模式
#define MODEL_OUT               1                                           //一般模式

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
        STATE_DRAWLINE,                                             //划线
        STATE_CLOSE                                                 //闭合状态
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

    virtual void setState(int state);                                   //设置状态

    virtual void released();

    //---------------------------------------------------------------------------------     

    void setPath(CPath* path);

    void setAreaIndex(int index, int areaIndex);                        //设置区间索引

    //-------------------------------------------------------------------------------- 

    void clearAreaIndex();                                              //清除区间

    CMargin* getMargin(int index);                                      //得到边界对象

    bool isCloseArea();                                                 //区域是否闭合     
 
    int hasPointInMargin(const Vec2& point);                            //点是否在边界上

    bool hasPointInArea(const Vec2& point);                             //点是否在区域内  

    int getNearMargin(const Vec2& point);                               //得到该点最近的边

    int getMode();                                                      //得到划线模式  

    void getMoveAble(const Vec2& inPoint, std::vector<int>& outDirect); //返回可行走区域

    int getMarginDirect(int direct);                                    //得到边界上的可行走方向 

    float getArea();                                                    //已解锁面积

    bool hasIncludeMaster();                                            //是否包含BOSS

    void clearSameLineNode(std::vector<Vec2>& outputVec);               //清理同方向节点    
  
    int getPositionType(const Vec2& inPos);                             //得到当前位置的类型

    int getTargetIndex(const  Vec2&);                                   //得到当前点位置的边界

    bool hasOverLoad(const Vec2& inPoint);

    std::vector< Vec2 > resultArea, addArea;

protected:

    void flushMargin();                                                 //刷新边界对象集合   

    void flush();                                                            

    CShape* createShape(int id, std::vector<Vec2>& refAllPoint);        //

    CShape* getShape(const int id);                                     //得到图形     

    void setMode(int mode);                                             //设置反向模式

    void checkMarginAvableDirect();                                     //补充检查可行走区域
   
private:

    //-----------------------------------------------------------------------------

    void addPoint(const Vec2& point);                                   //添加节点到尾部

    void getAllPoint(std::vector<Vec2>& outputVec);                     //返回所有节点

    unsigned int resetId();                                             //节点数  

    void delPoint(int index);                                           //删除单个节点

    void clearPoint();                                                  //清除所有节点

    TPoint* getPoint(int index);                                        //得到节点

	TPoint* getPoint(const Vec2& inPosition);                           //得到节点

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

    CPath*                          m_pPath;                            //路径

	int								m_iRorate;							//方向
    int                             m_Model;                            //模式

    std::map<Vec2, unsigned int>    m_oAllEndPoint;                     //所有端点可行走区域

    int                             m_Area[MAX_INDEX];                  //边界ID    
    std::map<int, CShape*>          m_oAllShape;                        //图形集合    

    CGameView*                      m_pGameView;
};                                              


#endif//__SHOWAREA_H__