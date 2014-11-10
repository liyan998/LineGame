#ifndef __MYSPRITE_H__
#define __MYSPRITE_H__

#include "System.h"

#include "State.h"
#include "Path.h"
#include "Game1Player.h"


class CShowArea;

#define MAX_ANGLE 4

/************************************************************************/
/* 



*/
/************************************************************************/
class CMySprite : 
public Sprite,
public CState, 
public CRander
{          

public:         

    enum State
    {
        STATE_INIT,         //
        STATE_STANDER,      //
        STATE_MOVE,         //
        STATE_DRAW,         //
        STATE_RUN           //          
    };

public:

    CREATE_FUNC( CMySprite )

public:

    virtual bool init();             

    virtual void setState(int state);

	virtual void print(DrawNode* dn);

	//----------------------------------------------------

	void setPath(CPath* path);

    void setPlayer(CGamePlayer* sp);

    void setShowArea(CShowArea* area);
                                                    
    void setPlayerPosition(const Vec2& pos);  

    //------------------------------------------------------

    void onPressed(const Vec2& vec2);             //

    void onMove(const Vec2& point);               // 

    //------------------------------------------------------

    void fixPosition(const Vec2& inPos, Vec2& outPos);
	

    void setSpStartPosition();							//����SP��ʼ������

    void setDirectStartPosition(const Vec2& point);		//���÷�������ʼ����

	void checkDirect(const Vec2& inPos);				//������

	void changeDirect(const Vec2& inPos ,int angle);

	int getAbsDistance();								//�õ���Ծ���

    void run(float tm);									//            

    void addGuide(const Vec2& point);

    void clearGuide();

   

private:                                                        

	int getFixAngle(int angle);                 //�����Ƕ�

    void spriteMove();                          //�����ƶ�          

private:                                             

    CPath*                  m_RefPath;

    CGamePlayer*            m_RefPlayer;

    CShowArea*              m_RefShowArea;


    std::vector<Vec2>       m_oTPath;            	

    float                   m_fStep;				//����

    Vec2                    m_oSpStartPosition;     //sp��ʼλ��
    Vec2                    m_oDirectStart;			//��������ʼ��

	Vec2					m_oAbsPosition;			//���λ����ʼ��
	Vec2					m_oEndPosition;

	int		                m_currentAngle;			//��ǰ�Ƕ�

    int                     m_iCountRecord;			//

};

#endif//__MYSPRITE_H__