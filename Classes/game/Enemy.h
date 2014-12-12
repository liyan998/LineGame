
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

    bool collwithBorder(const Vec2& inPoint);               //border碰撞

    bool collwithArea(const Vec2& inPoint);                 //Area碰撞

    bool collwithGuide(const Vec2& inPoint);                //Guide碰撞

public:

    CShowArea*          m_refShowArea;
    CMySprite*          m_refSp;

protected:
 
    int m_iStart;   //星级
    int m_iLevel;   //等级
    int m_iAttick;  //攻击力    
    int m_iLeader;  //领导力


};

#endif//__ENEMEY_H__