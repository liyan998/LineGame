/************************************************************************/
/* 
������������Ϸ��Ʒ����
��1��Ȧס�͵��߻��;���͹���
�� ��׼�����߽��湺���ã����������٣��ָ�����ʱ�����ֽ�����
�� ��Ϸ������ÿ��10����ڻ��������ˢ��һ��Ȧס�͵��ߣ�8�����ʧ���������˴����͵��ߵ��������ߡ�
�� ��Ϸ��ÿȦɱһ����������һ�������ڻ��������ˢ��һ��Ȧס�͵��ߣ�8�����ʧ���������˴����͵��ߵ��������ߡ�
�� ����Ϸ���������еĵ�����������ʱ�����ʹ���͵��ߣ�������������Ĭ����������

---------------------------------------------------------------------

����	����ð����50%���ƶ��ٶȣ�����5��	                200���	Ȧס��
�ָ�	�ָ�ð����25%������ֵ	                        100���	Ȧס��
��ʱ	����10���ͼʱ��	                            300���	Ȧס��
����	�ֵ�һ�λ���������ɱ���û���������ð���߲��᷵�ذ�ȫ��	500���	Ȧס��

��Ĭ	15������ֹ���й����ͷż���		                        Ȧס��
����	����ȫ��С�֣�����5��		                            Ȧס��
���	����ȫ������С��		                                Ȧס��
����	����ȫ��С�֣�����5��	                        20��ʯ	���ʹ����
��Ĭ	15������ֹ���й����ͷż���	                    20��ʯ	���ʹ����
����	����ȫ������С�ֵ�Ŀ��㣬����3��	                30��ʯ	���ʹ����
���	����ȫ������С��	                            30��ʯ	���ʹ����

---------------------------------------------------------------------

*/
/************************************************************************/
#ifndef __GAMEARTICLE_H__
#define __GAMEARTICLE_H__

#define TIME_DIS_ARTICLE    80   //��ʧʱ��
#define TIME_CREATE_ARTICLE 10  //��������ʱ��



//����
struct T_Property
{
    enum Category
    {
        CATEGORY_ADDSPEED       = 0x110,//�ٶ� 
        CATEGORY_ADDHEALTH      = 0x111,//�ָ�
        CATEGORY_ADDTIME        = 0x112,//��ʱ
        CATEGORY_ADDDPROTECT    = 0x113,//����

        CATEGORY_FREEZE         = 0x120,//����
        CATEGORY_SILENCE        = 0x121,//��Ĭ
        CATEGORY_TAUNT          = 0x122,//����
        CATEGORY_DESTORY        = 0x123 //����
    };

    int         category;               //��������
    int         eventid;                //�¼�ID
    EventParm   pData;                  //�¼����� 

    //--------------------------------------------
    
    const char* armtruename;            //��������
    const char* playlab;                //����

    //--------------------------------------------

    int         liveTime;               //����ʱ��
};      




class CGameArticle : public CGameElement
{
public:

    enum CreateType
    {
        SYSTEM, //ϵͳˢ��
        PAY,    //����
        DROP    //����
    };


public:

    static CGameArticle* create(CGameArticle* pArea)
    {
        CGameArticle* tp = new CGameArticle();


        if (tp->init())
        {

        }
        
        return tp;
    }

    CREATE_FUNC(CGameArticle)
    


public:

    enum State
    {
        STATE_DISP,     //��ʧ
        STATE_EFFE,     //���ŵ�����Ч
        STATE_ACTIVE    //����
    };

public:

    CGameArticle():
        m_iTimeCreate(0),
        m_iTimeDis(0),
        m_iCreateType(-1),
        m_pProperty(nullptr)
    {};

    virtual bool init();

    virtual void run(float time);

    virtual void print(DrawNode* dn);

    virtual void setState(int state); 
    
    virtual void released();

    //--------------------------------------

    void setCreateType(int type);               //���ô�������

    void setProperty(T_Property* pProperty);    //���õ�������

    void setProperty(int catetory);

    void animation_effe();                      //������Ч

    void movementCallback(Armature * armature, MovementEventType type, const std::string& name);

    inline int getCreateType(){ return this->m_iCreateType; };    

    //-----------------------------------------------

    int randProperty();                         //�������

private:

    //ϵͳˢ�µ���
    void action_Disp();

    void action_create();

private:

    int                 m_iTimeCreate;              //����ʱ���� 
    int                 m_iTimeDis;                 //����ʱ��

    int                 m_iCreateType;              //��������
    T_Property*         m_pProperty;                //��������
};

#endif//__GAMEARTICLE_H__