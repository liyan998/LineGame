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

    enum TagIndex
    {
        Anim_Light=0x13322,         //������
        Anim_idle,
        Anim_attick,
        Anim_seal
    };

    enum TornadoColor
    {
        COLOR_NONE,
        COLOR_BLACK = T_SkillDrogTornado::Color::TORNADO_COLOR_BLACK,
        COLOR_WHITE = T_SkillDrogTornado::Color::TORNADO_COLOR_WHITE
    };

    enum SkillId
    {
        SKILL_CONFUSE = 0X110100,  //�Ȼ���
    };

    enum SealState
    {
        SEALSTATE_NONE,
        SEALSTATE_ONAIR
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


    bool hasMoveSprite();
    
    int getStrackSize();

    const Vec2& getPlayerPosition();

    void changeDirect(int angle);


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


    void h_actionSkillAttick(EventParm pData);

    void h_actionSkillLightCount(EventParm pData);

    
    void h_actionSkillTornadoColor(EventParm pData);

    void h_actionCatSeal(EventParm pData);


    void setLigitPosition(const Vec2& inPos);

    void movementCallback(Armature * armature, MovementEventType type, const std::string& name);



    //------------------------------------------------
    
    void animation_idle();
    
    void animation_attack();  

    void animation_magic();

    void animation_seal();

    


    //���缼�ܹ���
    void setLightAttack(bool lightAttack);
    //���缼�ܹ�������
    void setLightAttackCount(int count);
    //���缼�ܹ����ͷ�
    void setLightAttickReleased();
    //���缼�ܹ������
    void destoryLightAttick();

    //------------------------------------
    //�ͷż���
    bool releasSkill(int skillid);

    bool releasSkillConfuse();                      //�Ȼ���

    void checkSkillConnfuse();

    int getSkillConfuseState();

    //---------------------------------------

    void setSealState(int state);                    //��ӡ

    int getSealState();

    void actionSeal(float time);



private:

    void checkEffect();

    void playerRun(float time);

    void playerStander(float time);


    //TODO ��ɶ���
    void animation_die();

    //TODO ��ɶ���
    void animation_move();   


public:
    
    bool                                m_bFlow;
    int                                 m_iCurrentDirect;    

    bool                                m_bHasLight;//�Ƿ��յ����繥������

    CAnimationAxis*                     m_pCurrentAnim;

private:   




    int                                 m_iSealState;
    float                               m_fSealTime;


    Vec2                                m_oCurrentTarget;
    Vec2                                m_oPlayerPosition;
    std::vector<Vec2>                   m_oAllGuide;

    int                                 m_iEffectAddSpeed;          //���ٵ���ʹ��
    T_EventPropertyAddSpeed*            m_pEventAddSpeed;

    int                                 m_iEffectAddProtect;        //������������

    int                                 m_iTornadoColor;            //��ħ������ �����

    std::map<int, const char*>          m_oDirectTab;               //
    int                                 m_iAnimDirect;              //��������


    int                                 m_iSkillConfuseState;       //�Ȼ���״̬
    unsigned int                        m_iSkillConfuseScore;       //�Ȼ��ܸ���
    int                                 m_iSkillTimeCount;

};


#endif//__PLAYER_H__