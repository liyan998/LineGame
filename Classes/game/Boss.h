
/************************************************************************/
/* 
文件名：Boss.h
功能描述： 游戏元素 


*/
/************************************************************************/

#ifndef __BOSS_H__
#define __BOSS_H__


class CBoss : public CEnemy
{

public:

    CREATE_FUNC(CBoss)

public:

    virtual bool init();

    virtual void run(float time);

    //----------------------------------------

    //休闲，移动，受击，死亡
    void animation_idle();

    void animation_move();

    void animation_die();

    void animation_attack();


};


#endif//__BOSS_H__