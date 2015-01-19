#ifndef __NPC_H__
#define __NPC_H__

/************************************************************************/
/* 
@file       Npc.h
@brief      守卫精灵功能定义
@auther     严黎刚    
*/
/************************************************************************/
class CNpc : public CEnemy
{

public:

    enum State
    {      
        STATE_LIVE,         //活动
        STATE_DIE,          //死亡
        STATE_REBACK        //复活
    };

public:

    CREATE_FUNC(CNpc)

public:

    virtual bool init();

    virtual void onEnter() override;

    virtual void run(float time);

    virtual void setState(int state);

    virtual void released();

    virtual void print(DrawNode* dn);

    virtual void changeDirect(int direct);

    //--------------------------------------

    void movementCallback(Armature * armature, MovementEventType type, const std::string& name);

    //-------------------------------------------------------

    inline void animation_reBack();             //复活

    inline void animation_Die();                //死亡

    inline void animation_move();               //移动

    void changeLiveDie(float time);

private:

    
    int m_iReLive;         //复活时间
};
#endif//__NPC_H__