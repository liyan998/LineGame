#ifndef __TORNADO_H__
#define __TORNADO_H__




class CTornado : public CEnemy
{
public:

    CREATE_FUNC( CTornado )

public:

    enum State
    {
        STATE_LIVE,    //»î¶¯
        STATE_DISAPPEAR//ÏûÊ§
    };

public:

    virtual bool init();

    virtual void onEnter();

    virtual void released();

    virtual void run(float time);

    virtual void changeDirect(int direct);

    virtual void setState(int state);

    virtual bool hasCollWithPlayer();

    //-------------------------------

    void setStyle(int color);


};
#endif//__TORNADO_H__
