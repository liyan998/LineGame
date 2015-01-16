#ifndef __DRAGON_H__
#define __DRAGON_H__


//风魔龙 闪电技能
struct T_SkillDragonLighing : T_SkillData
{
    float   m_fMaxTime;   //持续时间
    float   m_fTime;      //当前使用时间

    float   m_fCount;     //时间计数器  
    int     buffer;       //能量

    int state;

    virtual void init()
    {
        m_fTime     = m_fMaxTime;
        buffer      = 0;
        m_fCount    = 0;
        state       = 0;
    }
};


//风魔龙 风暴技能
struct T_SkillDrogTornado : T_SkillDataTime
{

    float m_fMAXWhiteTime;
    float m_fMAXBlackTime;

    float m_fWhiteTime;         //增加冒险者移动速度持续时间
    float m_fBlackTime;         //减少冒险者移动速度持续时间

    int currentColor;           //当前风的颜色

    enum Color
    {
        TORNADO_COLOR_BLACK = 2222,
        TORNADO_COLOR_WHITE = 1111
    }; 



    virtual void init()
    {
        T_SkillDataTime::init();

        currentColor = TORNADO_COLOR_WHITE;      

        m_fWhiteTime = 0;
        m_fBlackTime = 0;
    }
  
};

class CDragon : public CBoss,public CEventHandler
{

public:

    CREATE_FUNC(CDragon)

public:

    virtual bool init();

    virtual void onEnter();

    virtual void released();
    
    virtual void run(float time);

    virtual void randSkillRelease(float time);

    virtual void startRandSkill();

    virtual void changeDirect(int direct);

    virtual void actionEvent(int eventid, EventParm pData);

    virtual int getAttack();

    //-------------------------------------------------------------

    void skillLight(float time);

    void skillLightEnd();

    //---------------------------------------

    void skillTornado(float time);

    void skillTornadoWhite(T_SkillDrogTornado* pDr, float time);

    void skillTornadoBlack(T_SkillDrogTornado* pDr, float time);

    void skillTornadoEnd();


    void movementCallback(Armature * armature, MovementEventType type, const std::string& name);

private:

    std::map<int, const char*> m_oAngleTable;

};


#endif//__DRAGON_H__