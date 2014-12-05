#ifndef __GAME1PLAYER_H__
#define __GAME1PLAYER_H__

#include "System.h"
#include "GameState.h"
#include "Runnable.h"


#define INDEX_NONE -1

class CGamePlayer : public Node ,public CGameState, public CRunnable
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

    virtual void released();

    virtual void run(float time);
    //-----------------------------------------------------

    int getStep();

    void setPlayerPosition(const Vec2& pos);
   
    const Vec2& getPlsyerPosition();

   

    void setTarget(const Vec2& point);

    void addFollow(const Vec2& point);

    void backFollow();

    int getStrackSize();




private:    

    Sprite*             m_pSp;

    int                 m_iStep;

    int                 m_iCurrentDirect;

    Vec2                m_oCurrentTarget;

    

    std::vector<Vec2>   m_oAllGuide;

    
};


#endif//__PLAYER_H__