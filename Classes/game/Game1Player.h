#ifndef __GAME1PLAYER_H__
#define __GAME1PLAYER_H__

#include "EventSystem.h"

#define INDEX_NONE -1


class CGamePlayer : public CActor, public CEventHandler
{

public:

    enum State
    {
        STATE_STOP,
        STATE_RUN,
        STATE_STANDER,
        STATE_DIE           //����
    };

    enum Effect
    {
        EFFECT_NONE,        //
        EFFECT_ADDSPEED,    //����
        EFFECT_ADDPROTECTED,//����
    };

public:

    CREATE_FUNC( CGamePlayer )

public:
    
    virtual bool init();

    virtual void setState(int state);

    virtual void released();

    virtual void run(float time);

    virtual void print(DrawNode* dn);

    virtual int getStep();

    //-----------------------------------------------------
    
    int getStrackSize();

    const Vec2& getPlayerPosition();


    void setPlayerPosition(const Vec2& pos);   

    void checkPosition(const Vec2& inPoint); 

    void fixTargetPostion(const Vec2& inResPosition, const Vec2& inTargetPostion);   

    void setTarget(const Vec2& point);

    void addFollow(const Vec2& point);

    void backFollow();


    bool hasInProtected();

    void setProtectReleased();

    //---------------------------------------------

    void actionEvent(int eventid, EventParm pData);

    void h_actionAddSpeed(EventParm pData);

    void h_actionAddProtect(EventParm pData);



private:

    void checkEffect();

    void playerRun(float time);

    void playerStander(float time);

    //TODO ��ɶ���
    void animation_idle();

    //TODO ��ɶ���
    void animation_attack();  

    //TODO ��ɶ���
    void animation_die();

    //TODO ��ɶ���
    void animation_move();   


public:
    
    bool                                m_bFlow;
    int                                 m_iCurrentDirect;    

private:   

    Vec2                                m_oCurrentTarget;
    std::vector<Vec2>                   m_oAllGuide;

    int                                 m_iEffectAddSpeed;          //���ٵ���ʹ��
    T_EventPropertyAddSpeed*            m_pEventAddSpeed;

    int                                 m_iEffectAddProtect;        //������������



};


#endif//__PLAYER_H__