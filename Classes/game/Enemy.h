
/************************************************************************/
/* 
文件名:    Enemy.h
功能描述:   敌人

*/
/************************************************************************/
#ifndef __ENEMEY_H__
#define __ENEMEY_H__

class CEnemy : public CActor
{
                            
public:

    CEnemy() :m_iCollR(30){};


public:

    virtual void print(DrawNode* dn);

    virtual void changeDirect(int direct) = 0;

    //---------------------------------------------------------
    
    bool checkRandPosition(const Vec2& inPoint);                             //检查坐标是否符合游戏逻辑标准

    void randPosition();

    //----------------------------------------------

  

protected:

    bool collwithBorder(const Vec2& inPoint, Vec2& outPoint);               //border碰撞

    bool collwithArea(const Vec2& inPoint, Vec2& outPoint);                 //Area碰撞

    bool collwithGuide(const Vec2& inPoint, Vec2& outPoint);                //Guide碰撞


    void checkWith();
    

public:

    CShowArea*          m_refShowArea;


protected:
 
    int m_iStart;   //星级
    int m_iLevel;   //等级
    int m_iAttick;  //攻击力    
    int m_iLeader;  //领导力  


    int m_iCollR;   //碰撞半径
    
};

#endif//__ENEMEY_H__