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

#define DIRECT_CLOCKWISE        1                                           //闭合类型顺时针
#define DIRECT_ANTICCLOCKWISE   -1                                          //闭合类型逆时针

#define MODEL_IN                0                                           //内部模式
#define MODEL_OUT               1                                           //外部模式

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
        STATE_DRAWLINE,                                             //划线
        STATE_CLOSE                                                 //闭合状态
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

    virtual void setState(int state);                               //设置状态

    //---------------------------------------------------------------------------------     

    void setPath(CPath* path); 

    void setAreaIndex(int index, int areaIndex);                    //设置区间索引     

    //--------------------------------------------------------------------------------

    int getTargetIndex(const  Vec2&);                               //得到当前点位置的边界

    CMargin* getMargin(int index);                                  //得到边界对象   

    bool isCloseArea();                                             //区域是否闭合  
 
    void clearAreaIndex();                                          //清除区间
    
    bool hasPointInMargin(const Vec2& point);                       //点是否在边界上

    bool hasPointInArea(const Vec2& point);                         //点是否在区域内   

    int getMode();                                                  //得到划线模式

protected:

    void flushMargin();                                             //刷新边界对象集合   

    void flush();                                                            

    CShape* createShape(int id, std::vector<Vec2>& refAllPoint);    //

    CShape* getShape(const int id);                                 //得到图形

    int*    getMoveAble(const Vec2& pos);                           //返回可行走区域

    void setMode(int mode);                                         //设置反向模式    
   

private:

    //-----------------------------------------------------------------------------

    void addPoint(const Vec2& point);                               //添加节点到尾部

    void getAllPoint(std::vector<Vec2>& outputVec);                 //返回所有节点

    unsigned int resetId();                                         //节点数
                                                                            
    void delPoint(int start, int end, int category);                //删除节点

    void delPoint(int index);                                       //删除单个节点

    void insert(std::vector<Vec2>& allpint, int start, int end);    //插入节点

    void clearPoint();                                              //清除所有节点

    TPoint* getPoint(int index);                                    //得到节点

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
                                                                    

    CPath*                      m_pPath;                            //路径
    ClippingNode*               m_pClip;                            //

    int                         m_Area[MAX_INDEX];                  //边界ID            
    
    std::map<int, CShape*>      m_oAllShape;                        //图形集合  

    int                         m_Model;                            //模式
    
};                                              


#endif//__SHOWAREA_H__