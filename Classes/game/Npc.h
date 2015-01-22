#ifndef __NPC_H__
#define __NPC_H__

/************************************************************************/
/* 
@file       Npc.h
@brief      �������鹦�ܶ���
@auther     �����    
*/
/************************************************************************/
class CNpc : public CEnemy
{

public:

    enum State
    {      
        STATE_LIVE,         //�
        STATE_DIE,          //����
        STATE_REBACK        //����
    };


    enum IndexTag
    {
        INDEX_NPCINDEX_CONFUES = 0X112,  //������Ч
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

    virtual bool hasCollWithPlayer();

    //--------------------------------------

    void movementCallback(Armature * armature, MovementEventType type, const std::string& name);

    //-------------------------------------------------------

    inline void animation_reBack();             //����

    inline void animation_Die();                //����

    virtual void animation_move();              //�ƶ�

    void animation_confuse();

    void changeLiveDie(float time);

    //-------------------------------------

    void setPlayerSkillConfuse(int state);               //��Ҽ����Ȼ�

    void checkSkillConfuse(float time);


public:

    int m_iSkillConfuseState;                   //�Ȼ���

private:

    int m_iSkillConfuseCount;                   //ʱ��


    int m_iReLive;         //����ʱ��
};
#endif//__NPC_H__