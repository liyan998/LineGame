#ifndef __BUTTERFLY_H__
#define __BUTTERFLY_H__


//
struct T_SkillBigArea : T_SkillData
{
    float m_fArea;                  //���
    float m_skillTime;              //���ܳ���ʱ��
    float m_fMaxTime;               //����ʱ��

    virtual void init()
    {
        m_skillTime = m_fMaxTime;
    }
};

//
struct T_SkillFlush : T_SkillData
{
    int count;                      //���ִ���
    int m_iMaxCount;                //���ִ���

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


    virtual float getCollwithR();           //ɱ�˰뾶

    virtual bool hasKeepMoveing();

    virtual void randSkillRelease(float time);

    //--------------------------------------------------
    
    void releasFlush();                     //�ͷ�����


    void animation_move();
};

#endif//__BUTTERFLY_H__

