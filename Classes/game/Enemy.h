
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

protected:

    int m_iStart;   //�Ǽ�
    int m_iLevel;   //�ȼ�
    int m_iAttick;  //������
    int m_iStep;    //�ƶ��ٶ�
    int m_iLeader;  //�쵼��

};

#endif//__ENEMEY_H__