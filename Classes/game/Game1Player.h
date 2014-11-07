#ifndef __GAME1PLAYER_H__
#define __GAME1PLAYER_H__

#include "System.h"

class CGamePlayer : public Node
{
public:

    CREATE_FUNC( CGamePlayer )

    virtual bool init();

    //-----------------------------------------------------

    void setPlayerPosition(const Vec2& pos);

    void movePlayerTo(const Vec2& pos); 

    void moveToPath(const std::vector<Vec2>& allPoint);

    const Vec2& getPlsyerPosition();

private:

    Sprite* m_pSp;

    int m_iStep;
};


#endif//__PLAYER_H__