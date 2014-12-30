
/************************************************************************/
/* 
文件名：Boss.h
功能描述： 游戏元素 


*/
/************************************************************************/

#ifndef __BOSS_H__
#define __BOSS_H__


class CBoss : public CEnemy 
{

public:

    CREATE_FUNC(CBoss)

public:

    //随机技能状态
    enum RandSkill_State
    {
        RANDSKILL_STATE_WAITE,//等到倒计时
        RANDSKILL_STATE_RELEAS//释放
    };

    enum Skill
    {
        SKILL_NONE,
        SKILL_T_BIGAREA,    //炫彩蝶粉
        SKILL_T_FLUSH       //虚影蝶舞
    };

public:

    virtual bool init();

    virtual void onEnter();

    virtual void run(float time); 

    virtual void setState(int state);

    virtual void released();

    virtual void print(DrawNode* dn);

    virtual void changeDirect(int direct);

    virtual float getCollwithR();          //杀伤半径

    //----------------------------------------

    void animation_move();      

    void movementCallback(Armature * armature, MovementEventType type, const std::string& name);

    //-----------------------------------------

    void randSkillTimer();      //随机技能

    void createSkillTimer();

    

private:

    int m_iSkillTimer;              //随机技能创建时间

    float m_iSkillCd;               //随机技能持续时间

    int m_iSkillState;              //技能状态

};


#endif//__BOSS_H__