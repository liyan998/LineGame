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



    virtual void actionEvent(int eventid, EventParm pData);


    void skillLight(float time);

    void skillLightEnd();
};


#endif//__DRAGON_H__