
/************************************************************************/
/* 
�ļ���:    Enemy.h
��������:   ����

*/
/************************************************************************/
#ifndef __ENEMEY_H__
#define __ENEMEY_H__

class CEnemy : public CActor
{
                            
public:


public:


    virtual void changeDirect(int direct) = 0;

    
    //---------------------------------------------------------
    
    inline int getAttack();                                                 //������   

    //----------------------------------------------
    
protected:

    bool collwithGuide(const Vec2& inPoint, Vec2& outPoint);                //Guide��ײ

    void checkWith();

    bool collwithPlayer(const Vec2& inPoint);                               //�Ƿ�����ҽ�ɫ��ײ
    
public:

    CGamePlayer*    m_refPlayer;
 
protected:

    int             m_iStart;   //�Ǽ�
    int             m_iLevel;   //�ȼ�
    int             m_iAttick;  //������    
    int             m_iLeader;  //�쵼��  


   
    
};

#endif//__ENEMEY_H__