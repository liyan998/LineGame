#ifndef __BUTTERFLY_H__
#define __BUTTERFLY_H__


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



class CButterFly : public CBoss
{

public:

    CREATE_FUNC(CButterFly)

public:

    virtual bool init();

    virtual void onEnter();


    virtual void run(float time);


    virtual float getCollwithR();           //杀伤半径

    virtual bool hasKeepMoveing();

    virtual void randSkillRelease(float time);

    //--------------------------------------------------
    
    void releasFlush();                     //释放闪击


    void animation_move();
};

#endif//__BUTTERFLY_H__

