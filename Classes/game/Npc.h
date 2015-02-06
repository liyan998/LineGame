#ifndef __NPC_H__
#define __NPC_H__

/************************************************************************/
/* 
@file       Npc.h
@brief      �������鹦�ܶ���
@auther     �����    
*/
/************************************************************************/
class CNpc : public CEnemy, public CEventHandler
{

public:

    enum State
    {      
        STATE_LIVE,         //�
        STATE_DIE,          //����
        STATE_REBACK,       //����
        STATE_FREEZE        //����
    };


    enum IndexTag
    {
        INDEX_NPCINDEX_CONFUES = 0X112,  //������Ч
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

    inline void animation_reBack();             //����

    inline void animation_Die();                //����

    virtual void animation_move() = 0;              //�ƶ�

    virtual void animation_stop() = 0;

    void animation_confuse();

    void changeLiveDie(float time);

    //-------------------------------------

    void setPlayerSkillConfuse(int state);               //��Ҽ����Ȼ�

    void checkSkillConfuse(float time);

    //-------------------------------------------

    void h_actionPlayerReleaseProperty(EventParm pData);

    void checkFreeze(float time);

public:

    int m_iSkillConfuseState;                   //�Ȼ���

    float m_fFreezeTime;                          //����ʱ��

private:

    int m_iSkillConfuseCount;                   //ʱ��


    int m_iReLive;                              //����ʱ��
};
#endif//__NPC_H__