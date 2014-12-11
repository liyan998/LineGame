
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

    bool collwithBorder(const Vec2& inPoint);               //border��ײ

    bool collwithArea(const Vec2& inPoint);                 //Area��ײ

public:

    CShowArea*          m_refShowArea;


protected:


    int m_iStart;   //�Ǽ�
    int m_iLevel;   //�ȼ�
    int m_iAttick;  //������    
    int m_iLeader;  //�쵼��


};

#endif//__ENEMEY_H__