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
        STATE_DIE           //死亡
    };

    enum Effect
    {
        EFFECT_NONE,        //
        EFFECT_ADDSPEED,    //加速
        EFFECT_ADDPROTECTED,//护盾
    };

    enum TagIndex
    {
        Anim_Light=0x13322,         //闪击云
        Anim_idle,
        Anim_attick
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


    //--------------------------------------------------------

    void h_actionSkillStart(EventParm pData);

    void h_actionSkillEnd(EventParm pData);

    void setLigitPosition(const Vec2& inPos);

    void h_actionSkillAttick(EventParm pData);

    void h_actionSkillLightCount(EventParm pData);

    void movementCallback(Armature * armature, MovementEventType type, const std::string& name);


    //------------------------------------------------
    
    void animation_idle();
    
    void animation_attack();  

    CAnimationAxis* findCreateByIndex(int index);


    //闪电技能攻击
    void setLightAttack(bool lightAttack);
    //闪电技能攻击计数
    void setLightAttackCount(int count);
    //闪电技能攻击释放
    void setLightAttickReleased();
    //闪电技能攻击完成
    void destoryLightAttick();

private:

    void checkEffect();

    void playerRun(float time);

    void playerStander(float time);


    //TODO 完成动画
    void animation_die();

    //TODO 完成动画
    void animation_move();   


public:
    
    bool                                m_bFlow;
    int                                 m_iCurrentDirect;    

    bool                                m_bHasLight;//是否收到闪电攻击作用

    CAnimationAxis*                     m_pCurrentAnim;

private:   

    Vec2                                m_oCurrentTarget;
    Vec2                                m_oPlayerPosition;
    std::vector<Vec2>                   m_oAllGuide;

    int                                 m_iEffectAddSpeed;          //加速道具使用
    T_EventPropertyAddSpeed*            m_pEventAddSpeed;

    int                                 m_iEffectAddProtect;        //防护道具作用



};


#endif//__PLAYER_H__