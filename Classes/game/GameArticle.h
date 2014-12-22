/************************************************************************/
/* 
功能描述：游戏物品定义
（1）圈住型道具获得途径和规则：
① 在准备道具界面购买获得，包括：加速，恢复，补时，开局解锁；
② 游戏过程中每隔10秒会在画线区随机刷出一个圈住型道具，8秒后消失，包括除了触发型道具的其他道具。
③ 游戏中每圈杀一个护卫会有一定概率在画线区随机刷出一个圈住型道具，8秒后消失，包括除了触发型道具的其他道具。
④ 在游戏场景界面中的道具栏可以随时购买的使用型道具，包括冰冻，沉默，嘲讽，消除

---------------------------------------------------------------------

加速	增加冒险者50%的移动速度，持续5秒	                200金币	圈住型
恢复	恢复冒险者25%的生命值	                        100金币	圈住型
补时	增加10秒解图时间	                            300金币	圈住型
防护	抵挡一次护卫攻击并杀死该护卫，而且冒险者不会返回安全线	500金币	圈住型
沉默	15秒内阻止所有怪物释放技能		                        圈住型
冰冻	冻结全屏小怪，持续5秒		                            圈住型
清除	消灭全屏所有小怪		                                圈住型
冰冻	冻结全屏小怪，持续5秒	                        20钻石	点击使用型
沉默	15秒内阻止所有怪物释放技能	                    20钻石	点击使用型
嘲讽	吸引全屏所有小怪到目标点，持续3秒	                30钻石	点击使用型
清除	消灭全屏所有小怪	                            30钻石	点击使用型

---------------------------------------------------------------------

*/
/************************************************************************/
#ifndef __GAMEARTICLE_H__
#define __GAMEARTICLE_H__

#define TIME_DIS_ARTICLE    8   //消失时间
#define TIME_CREATE_ARTICLE 10  //创建道具时间

class CGameArticle : public CGameElement
{

public:

    CREATE_FUNC(CGameArticle)

public:

    enum State
    {
        STATE_DISP,     //消失
        STATE_EFFE,     //播放道具特效
        STATE_ACTIVE    //激活
    };

public:

    CGameArticle():
        m_iTimeCreate(0),
        m_iTimeDis(0){};

    virtual bool init();

    virtual void run(float time);

    virtual void print(DrawNode* dn);

    virtual void setState(int state); 
    
    virtual void released();

    //--------------------------------------

    int getDrop();

    void animation_effe();//道具特效

private:

    void action_Disp();

    void action_create();

private:

    int m_iTimeCreate;

    int m_iTimeDis;
};

#endif//__GAMEARTICLE_H__