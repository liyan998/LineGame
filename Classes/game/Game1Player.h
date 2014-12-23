#ifndef __GAME1PLAYER_H__
#define __GAME1PLAYER_H__

#include "GameElement.h"

#define INDEX_NONE -1


class CGamePlayer : public CActor
{

public:

    enum State
    {
        STATE_STOP,
        STATE_RUN,
        STATE_STANDER,
        STATE_DIE           //死亡
    };


public:

    CREATE_FUNC( CGamePlayer )

    virtual bool init();

    virtual void setState(int state);

    virtual void released();

    virtual void run(float time);

    virtual void print(DrawNode* dn);


    //-----------------------------------------------------

    int getStep();

    void setPlayerPosition(const Vec2& pos);
   
    const Vec2& getPlsyerPosition();

    void checkPosition(const Vec2& inPoint); 

    void fixTargetPostion(const Vec2& inResPosition, const Vec2& inTargetPostion);   

    void setTarget(const Vec2& point);

    void addFollow(const Vec2& point);    

    void backFollow();

    int getStrackSize();



    //TODO 完成动画
    void animation_idle();

    //TODO 完成动画
    void animation_attack();  

    //TODO 完成动画
    void animation_die();

    //TODO 完成动画
    void animation_move();         


    bool                m_bFlow;

   // CMySprite*          m_refSp;

    int                 m_iCurrentDirect;

private:    

    //cocostudio::Armature*               m_pSp;

   
    Vec2                                m_oCurrentTarget;
    std::vector<Vec2>                   m_oAllGuide;

};


#endif//__PLAYER_H__