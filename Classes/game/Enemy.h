
/************************************************************************/
/* 
文件名:    Enemy.h
功能描述:   敌人

*/
/************************************************************************/
#ifndef __ENEMEY_H__
#define __ENEMEY_H__

class CEnemy : public CActor
{

protected:

    int m_iStart;   //星级
    int m_iLevel;   //等级
    int m_iAttick;  //攻击力
    int m_iStep;    //移动速度
    int m_iLeader;  //领导力

};

#endif//__ENEMEY_H__