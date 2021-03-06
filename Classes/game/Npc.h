#ifndef __NPC_H__
#define __NPC_H__

/************************************************************************/
/* 
@file       Npc.h
@brief      守卫精灵功能定义
@auther     严黎刚    
*/
/************************************************************************/
class CNpc : public CEnemy, public CEventHandler
{

public:

    enum State
    {      
        STATE_LIVE,         //活动
        STATE_DIE,          //死亡
        STATE_REBACK,       //复活
        STATE_FREEZE        //冰冻
    };


    enum IndexTag
    {
        INDEX_NPCINDEX_CONFUES = 0X112,  //技能特效
    };
// public:
// 
//     CREATE_FUNC(CNpc)

public:

    virtual bool init();

    virtual void onEnter() override;

    virtual void run(float time);

    virtual void setState(int state);

    virtual void released();

    virtual void print(DrawNode* dn);

    virtual void changeDirect(int direct);

    virtual bool hasCollWithPlayer();

    virtual void actionEvent(int eventid, EventParm pData);

  

    //--------------------------------------

    void movementCallback(Armature * armature, MovementEventType type, const std::string& name);

    //-------------------------------------------------------

    inline void animation_reBack();             //复活

    inline void animation_Die();                //死亡

    virtual void animation_move() = 0;              //移动

    virtual void animation_stop() = 0;

    void animation_confuse();

    void changeLiveDie(float time);

    //-------------------------------------

    void setPlayerSkillConfuse(int state);               //玩家技能魅惑

    void checkSkillConfuse(float time);

    //-------------------------------------------

    void h_actionPlayerReleaseProperty(EventParm pData);

    void checkFreeze(float time);

public:

    int m_iSkillConfuseState;                   //魅惑技能

    float m_fFreezeTime;                        //冰冻时间

private:

    int m_iSkillConfuseCount;                   //时间


    int m_iReLive;                              //复活时间
};
#endif//__NPC_H__