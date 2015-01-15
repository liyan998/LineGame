
/************************************************************************/
/* 
�ļ�����Boss.h
���������� ��ϷԪ�� 


*/
/************************************************************************/

#ifndef __BOSS_H__
#define __BOSS_H__


//��������
struct T_SkillData
{
    virtual void init() = 0;
};

//�������� + ����ʱ��
struct T_SkillDataTime : T_SkillData
{
    float   m_fMaxTime;   //����ʱ��
    float   m_fTime;      //��ǰʹ��ʱ�� 

    virtual void init()
    {
        m_fTime = m_fMaxTime;
    }
};


///.................................................................
//�������
struct T_RandSkill
{
    int             m_iMaxCD;       //����CD

    int             m_iSkillCd;     //�漼��CD
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

        SKILL_T_LIGHTING,   //��ħ��������
        SKILL_T_TORNADO,    //�����
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

    //�Ƿ�����ƶ�
    virtual bool hasKeepMoveing();
    //�ͷ��������
    virtual void randSkillRelease(float time);
    //��ʼ�ͷ��������
    virtual void startRandSkill();

    //----------------------------------------

    //void animation_move();
   

    //void movementCallback(Armature * armature, MovementEventType type, const std::string& name);

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