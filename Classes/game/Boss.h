
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

    virtual void onEnter();

    virtual void run(float time); 

    virtual void setState(int state);

    virtual void released();

    virtual void print(DrawNode* dn);

    virtual void changeDirect(int direct);

    //----------------------------------------

    void animation_move();      

    void movementCallback(Armature * armature, MovementEventType type, const std::string& name);
private:

    cocostudio::Armature* m_pArmature;
    
};


#endif//__BOSS_H__