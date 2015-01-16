#ifndef __DRAGON_H__
#define __DRAGON_H__


//��ħ�� ���缼��
struct T_SkillDragonLighing : T_SkillData
{
    float   m_fMaxTime;   //����ʱ��
    float   m_fTime;      //��ǰʹ��ʱ��

    float   m_fCount;     //ʱ�������  
    int     buffer;       //����

    int state;

    virtual void init()
    {
        m_fTime     = m_fMaxTime;
        buffer      = 0;
        m_fCount    = 0;
        state       = 0;
    }
};


//��ħ�� �籩����
struct T_SkillDrogTornado : T_SkillDataTime
{

    float m_fMAXWhiteTime;
    float m_fMAXBlackTime;

    float m_fWhiteTime;         //����ð�����ƶ��ٶȳ���ʱ��
    float m_fBlackTime;         //����ð�����ƶ��ٶȳ���ʱ��

    int currentColor;           //��ǰ�����ɫ

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