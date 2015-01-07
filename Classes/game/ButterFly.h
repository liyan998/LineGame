#ifndef __BUTTERFLY_H__
#define __BUTTERFLY_H__



class CButterFly : public CBoss
{

public:

    CREATE_FUNC(CButterFly)

public:

    virtual bool init();

    virtual void onEnter();


    virtual void run(float time);


    virtual float getCollwithR();           //…±…À∞Îæ∂

    virtual bool hasKeepMoveing();

    virtual void randSkillRelease();

    //--------------------------------------------------
    
    void releasFlush();                     // Õ∑≈…¡ª˜


    void animation_move();
};

#endif//__BUTTERFLY_H__

