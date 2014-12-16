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
        STATE_LIVE,     //活动
        STATE_DIE       //死亡
    };

public:

    CREATE_FUNC(CNpc)

public:

    virtual void onEnter() override;

    virtual void run(float time);

    virtual void setState(int state);

    virtual void released();

    //--------------------------------------


private:

    
};
#endif//__NPC_H__