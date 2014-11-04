#ifndef __SHOWAREA_H__
#define __SHOWAREA_H__

#include "System.h"
#include "Margin.h"  
#include "Shape.h"
#include "MySprite.h"  

//////////////////////////////////////////////////////////////////////////////////////
                                        

#define SELECTID_NULL   -1                                          //边界选择ID NULL

#define MAX_INDEX       2                                           //连接节点数 起始， 终止

#define SHAPEID_AREA    11                                          //图形ID 封闭区域   
#define SHAPEID_TEMP    12                                          //图形ID 临时区域  

#define CLOSETYPE_1     1                                           //闭合类型

//////////////////////////////////////////////////////////////////////////////////////


class CShowArea : 
    public Sprite , 
    public CRander , 
    public CState
{
public:

    enum State
    {
        STATE_DRAWLINE,                                             //划线
        STATE_CLOSE                                                 //闭合状态
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

    virtual void setState(int state);                               //设置状态

    //---------------------------------------------------------------------------------

    void setPlayer(CMySprite*);

    void setPath(CPath* path);

    void setPlayerPosiztion();

    void setPlayerPosiztion(const Vec2& vec2, int index);  

    void setAreaIndex(int index, int areaIndex);                    //设置区间索引     

    int getTargetIndex(const  Vec2&);                               //得到当前点位置的边界

    CMargin* getMargin(int index);                                  //得到边界对象      

    bool isCloseArea();                                             //区域是否闭合

    void runMove(float inv);                                        //执行运动
 
    void clearAreaIndex();                                          //清除区间
    
    bool hasPointInMargin(const Vec2& point);                       //点是否在边界上

    bool hasPointInArea(const Vec2& point);                         //点是否在区域内

    void flushMargin();                                             //刷新边界对象集合   

    void flush();

    CShape* createShape(int id, std::vector<Vec2>& refAllPoint);    //

    CShape* getShape(const int id);                                 //得到图形

    int*    getMoveAble(const Vec2& pos);                           //返回可行走区域

private:

    void closeArea(int category);                                   //闭合区域 


private:

    DrawNode*                   m_pDrawNode;                        //
    std::vector< Vec2 >         m_oAllPoint;                        //
    std::vector< Vec2 >         m_oTempPoint;                       //
    std::vector< int >          m_oAllMargin;                       //      
                                                                    
    CMySprite*                  m_pPlayer;                          //
    CPath*                      m_pPath;                            //路径
    ClippingNode*               m_pClip;                            //

    int                         m_Area[MAX_INDEX];                  //边界ID            
    
    std::map<int, CShape*>      m_oAllShape;                        //图形集合                   
    
};                                              


#endif//__SHOWAREA_H__