#ifndef __MYSPRITE_H__
#define __MYSPRITE_H__

#include "System.h"

#include "Runnable.h"
#include "GameState.h"
#include "Path.h"
#include "Game1Player.h"


class CGameView;
class CShowArea;

#define MAX_ANGLE 4

/************************************************************************/
/* 



*/
/************************************************************************/
class CMySprite : 
public Sprite,
public CGameState, 
public CRander ,
public CRunnable
{          

public:         

    enum State
    {
        STATE_INIT,         //
        STATE_STANDER,      //
        STATE_MOVE,         //
        STATE_DRAW,         //
        STATE_CLOSE,        //
        STATE_BACK          //          
    };

public:

    CREATE_FUNC( CMySprite )

public:

    virtual bool init();             

    virtual void setState(int state);

	virtual void print(DrawNode* dn);

    virtual void released();

    virtual void run(float time);        

	//----------------------------------------------------

    inline void setPath(CPath* path){ this->m_RefPath = path; }

    inline void setPlayer(CGamePlayer* sp){ this->m_RefPlayer = sp; }

    inline void setShowArea(CShowArea* area){ this->m_RefShowArea = area; }

    inline void setGameView(CGameView* pGameView){ this->m_RefGameView = pGameView;  }
                                                    
    inline void setPlayerPosition(const Vec2& pos)
    { 
        m_oSpCurrentPos = pos;
        m_RefPlayer->setPlayerPosition(pos);
    }

    inline float getSpStep(){return this->m_fStep;}

    //------------------------------------------------------

    void onPressed(const Vec2& pointer);                //     

    void onMove(const Vec2& pointer);                   // 

    void onReleased(const Vec2& pointer);

    //------------------------------------------------------  

   

private:

    void fixPosition(const Vec2& inPos, Vec2& outPos);  //����λ�� 

    void playerMove(const Vec2& spPosition);            //�����ƶ� 

    void setSpStartPosition();							//����SP��ʼ������

    void setDirectStartPosition(const Vec2& point);		//���÷�������ʼ����

	void checkDirect(const Vec2& inPos);				//������

	void changeDirect(const Vec2& inPos ,int angle);    //����ı�
    

    bool hasRevceDircet(int direct, int fixangle);      //�Ƿ������˶�

	int getAbsDistance();								//�õ���Ծ���

   	

    //----------------------------------------------------------------------            

    void addGuide(const Vec2& point);

    void backGuide();                                   //�Ƴ��ڵ�

    void clearGuide();

    //---------------------------------------------------------------------- 

    void checkBack();

    void runback();

    void checkGo();

    void runGo();

    //---------------------------------------------------------------------- 

    void onMoveToDraw();

    void onStander(const Vec2& inPoint);
                                               
    void onDrawToClose(const Vec2& inPoint);      

    bool hasMoveAction();

    bool hasBreakMoveInLine();
  


private:                                                        

	int getFixAngle(int angle);                         //�����Ƕ�

    void fixPath(const Vec2& inPoint);

private:                                             

    CPath*                  m_RefPath;

    CGamePlayer*            m_RefPlayer;

    CShowArea*              m_RefShowArea; 

    CGameView*              m_RefGameView;

    std::vector<Vec2>       m_oTPath;            	

    float                   m_fStep;				//����

    int                     m_curMarginIndex;       //��ǰѡ���

    //-----------------------------------------------------------------

    Vec2                    m_oSpCurrentPos;        //SP��ǰλ��

    Vec2                    m_oSpStartPos;          //sp��ʼλ��

    Vec2                    m_oSpTarget;            //spRebackTarget \
   
    //���Ʋ���--------------------------------------------------------

	int		                m_currentAngle;			//��ǰ�Ƕ� | back currentAngle 

    Vec2                    m_oDirectStart;			//��������ʼ�� 

	Vec2					m_oAbsStartPos;	        //���λ����ʼ��

	Vec2					m_oAbsEndPos;           //���λ���յ�

    int                     m_iCountRecord;			//

    //----------------------------------------------------

    Vec2                    m_oGuideLStart;

    Vec2                    m_oGuideLEnd;

    

};

#endif//__MYSPRITE_H__