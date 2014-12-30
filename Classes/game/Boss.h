
/************************************************************************/
/* 
�ļ�����Boss.h
���������� ��ϷԪ�� 


*/
/************************************************************************/

#ifndef __BOSS_H__
#define __BOSS_H__


class CBoss : public CEnemy 
{

public:

    CREATE_FUNC(CBoss)

public:

    //�������״̬
    enum RandSkill_State
    {
        RANDSKILL_STATE_WAITE,//�ȵ�����ʱ
        RANDSKILL_STATE_RELEAS//�ͷ�
    };

    enum Skill
    {
        SKILL_NONE,
        SKILL_T_BIGAREA,    //�Ųʵ���
        SKILL_T_FLUSH       //��Ӱ����
    };

public:

    virtual bool init();

    virtual void onEnter();

    virtual void run(float time); 

    virtual void setState(int state);

    virtual void released();

    virtual void print(DrawNode* dn);

    virtual void changeDirect(int direct);

    virtual float getCollwithR();          //ɱ�˰뾶

    //----------------------------------------

    void animation_move();      

    void movementCallback(Armature * armature, MovementEventType type, const std::string& name);

    //-----------------------------------------

    void randSkillTimer();      //�������

    void createSkillTimer();

    

private:

    int m_iSkillTimer;              //������ܴ���ʱ��

    float m_iSkillCd;               //������ܳ���ʱ��

    int m_iSkillState;              //����״̬

};


#endif//__BOSS_H__