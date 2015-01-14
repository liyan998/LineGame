#ifndef __DRAGON_H__
#define __DRAGON_H__



class CDragon : public CBoss,public CEventHandler
{

public:

    CREATE_FUNC(CDragon)

public:

    virtual bool init();

    virtual void onEnter();

    virtual void released();
    
    virtual void run(float time);

    virtual void randSkillRelease(float time);

    virtual int getAttack();

    virtual void startRandSkill();

    virtual void changeDirect(int direct);

    virtual void actionEvent(int eventid, EventParm pData);


    void skillLight(float time);

    void skillLightEnd();


    void movementCallback(Armature * armature, MovementEventType type, const std::string& name);

private:

    std::map<int, const char*> m_oAngleTable;

};


#endif//__DRAGON_H__