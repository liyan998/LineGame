
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

    //virtual void print(DrawNode* dn);

    virtual void changeDirect(int direct) = 0;

    //---------------------------------------------------------
    
//     bool checkRandPosition(const Vec2& inPoint);                             //��������Ƿ������Ϸ�߼���׼
// 
    //void randPosition();

    //----------------------------------------------

  

protected:

                //Area��ײ

    bool collwithGuide(const Vec2& inPoint, Vec2& outPoint);                //Guide��ײ


    void checkWith();
    

public:



protected:
 
    int m_iStart;   //�Ǽ�
    int m_iLevel;   //�ȼ�
    int m_iAttick;  //������    
    int m_iLeader;  //�쵼��  


   
    
};

#endif//__ENEMEY_H__