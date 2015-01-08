
/************************************************************************/
/* 
文件名：Boss.h
功能描述： 游戏元素 


*/
/************************************************************************/

#ifndef __BOSS_H__
#define __BOSS_H__



struct T_SkillData
{
    virtual void init() = 0;
};

//
struct T_SkillBigArea : T_SkillData
{
    float m_fArea;                  //面积
    float m_skillTime;              //技能持续时间
    float m_fMaxTime;               //持续时间

    virtual void init()
    {
        m_skillTime = m_fMaxTime;
    }
};

//
struct T_SkillFlush : T_SkillData
{
    int count;                      //闪现次数
    int m_iMaxCount;                //闪现次数

    virtual void init()
    {
        count = m_iMaxCount;
    }
};

//风魔龙 闪电技能
struct T_SkillDragonLighing
{
    float   m_fMaxTime;   //持续时间
    float   m_fTime;      //当前使用时间

    float   m_fCount;     //时间计数器  
    int   buffer;       //能量

    int state;

    virtual void init()
    {
        m_fTime = m_fMaxTime;
        buffer  = 0;
        m_fCount = 0;
        state = 0;
    }

};

///.................................................................

struct T_RandSkill
{
    int             m_iMaxCD;

    int             m_iSkillCd;     //随机技能CD
    int             m_iSkillId;     //技能ID

    int             m_iSkillState;  //技能状态

    T_SkillData*    m_pSkill; 

    void init()
    {
        m_iSkillCd = m_iMaxCD;
        m_pSkill->init();
    }
};



////////////////////////////////////////////////////////////////


class CBoss : public CEnemy 
{

public:

    CREATE_FUNC(CBoss)

public:

    //随机技能状态
    enum RandSkill_State
    {
        RANDSKILL_STATE_CD,     //不可释放cd
        RANDSKILL_STATE_READY,  //可释放
        RANDSKILL_STATE_RELEAS  //释放
    };

    enum Skill
    {
        SKILL_NONE,
        SKILL_T_BIGAREA,    //炫彩蝶粉
        SKILL_T_FLUSH,      //虚影蝶舞
        SKILL_T_LIGHTING    //风魔龙闪电云
    };

public:

    CBoss() :
        m_pRandSkill(nullptr), 
        m_fSkillCdCount(0.f)
    {}

    virtual bool init();

    virtual void onEnter();

    virtual void run(float time); 

    virtual void setState(int state);

    virtual void released();

    virtual void print(DrawNode* dn);

    virtual void changeDirect(int direct);

    //virtual float getCollwithR();          //杀伤半径

    virtual bool hasKeepMoveing();

    virtual void randSkillRelease(float time);

    //----------------------------------------

    //void animation_move();
   

    void movementCallback(Armature * armature, MovementEventType type, const std::string& name);

    //-----------------------------------------


    void randSkillTimer(float time);      //随机技能

    void createSkillTimer();

    void randSkillCreate();


    void skillCd();             //技能CD

    

protected:

    int                             m_iSkillTimer;                  //系统创建随机技能时间
    T_RandSkill*                    m_pRandSkill;
    std::vector<T_RandSkill*>       m_oAllRandSkill;
    int                             m_iRandSkillState;              //技能状态

    float                           m_fSkillCdCount;                //技能CD计时器
};


#endif//__BOSS_H__