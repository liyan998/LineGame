
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

 

    virtual void setState(int state);

    virtual void released();

    virtual void print(DrawNode* dn);

    //----------------------------------------

    void animation_move();  


    float               m_fCount;

private:

    cocostudio::Armature* m_pArmature;
    
};


#endif//__BOSS_H__