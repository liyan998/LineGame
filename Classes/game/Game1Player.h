#ifndef __GAME1PLAYER_H__
#define __GAME1PLAYER_H__

#include "System.h"
#include "State.h"
#include "Margin.h"

class CGamePlayer : public Node ,public CState
{

public:

    enum State
    {
        STATE_STOP,
        STATE_RUN,
        STATE_STANDER
    };


public:

    CREATE_FUNC( CGamePlayer )

    virtual bool init();

    virtual void setState(int state);

    //-----------------------------------------------------

    void setPlayerPosition(const Vec2& pos);

    void movePlayerTo(const Vec2& start, const Vec2& pos); 

    void moveToPath(const std::vector<Vec2>& allPoint);

    const Vec2& getPlsyerPosition();

    void run(float time);

private:
              
    CMargin     m_oMargin;

    Sprite*     m_pSp;

    int         m_iStep;
};


#endif//__PLAYER_H__