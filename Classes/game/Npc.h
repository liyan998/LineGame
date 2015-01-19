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

    //--------------------------------------

    void movementCallback(Armature * armature, MovementEventType type, const std::string& name);

    //-------------------------------------------------------

    inline void animation_reBack();             //����

    inline void animation_Die();                //����

    inline void animation_move();               //�ƶ�

    void changeLiveDie(float time);

private:

    
    int m_iReLive;         //����ʱ��
};
#endif//__NPC_H__