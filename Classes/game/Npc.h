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
        STATE_LIVE,     //�
        STATE_DIE       //����
    };

public:

    CREATE_FUNC(CNpc)

public:

    virtual void onEnter() override;

    virtual void run(float time);

    virtual void setState(int state);

    virtual void released();

    //--------------------------------------


private:

    
};
#endif//__NPC_H__