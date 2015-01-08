
/************************************************************************/
/* 
�ļ�����Boss.h
���������� ��ϷԪ�� 


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

//��ħ�� ���缼��
struct T_SkillDragonLighing
{
    float   m_fMaxTime;   //����ʱ��
    float   m_fTime;      //��ǰʹ��ʱ��

    float   m_fCount;     //ʱ�������  
    int   buffer;       //����

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

    int             m_iSkillCd;     //�������CD
    int             m_iSkillId;     //����ID

    int             m_iSkillState;  //����״̬

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

    //�������״̬
    enum RandSkill_State
    {
        RANDSKILL_STATE_CD,     //�����ͷ�cd
        RANDSKILL_STATE_READY,  //���ͷ�
        RANDSKILL_STATE_RELEAS  //�ͷ�
    };

    enum Skill
    {
        SKILL_NONE,
        SKILL_T_BIGAREA,    //�Ųʵ���
        SKILL_T_FLUSH,      //��Ӱ����
        SKILL_T_LIGHTING    //��ħ��������
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

    //virtual float getCollwithR();          //ɱ�˰뾶

    virtual bool hasKeepMoveing();

    virtual void randSkillRelease(float time);

    //----------------------------------------

    //void animation_move();
   

    void movementCallback(Armature * armature, MovementEventType type, const std::string& name);

    //-----------------------------------------


    void randSkillTimer(float time);      //�������

    void createSkillTimer();

    void randSkillCreate();


    void skillCd();             //����CD

    

protected:

    int                             m_iSkillTimer;                  //ϵͳ�����������ʱ��
    T_RandSkill*                    m_pRandSkill;
    std::vector<T_RandSkill*>       m_oAllRandSkill;
    int                             m_iRandSkillState;              //����״̬

    float                           m_fSkillCdCount;                //����CD��ʱ��
};


#endif//__BOSS_H__