#ifndef __SKILL_H__
#define __SKILL_H__
/************************************************************************/
/* 
@berf ��Ҽ���
@auth 
*/
/************************************************************************/

//�Ȼ���״̬
enum SkillConfuseState
{
    SKILLSTATE_CD,          //����CD
    SKILLSTATE_READY,       //���ͷ�

    SKILLSTATE_NONE,        //����δ��ʹ��
    SKILLSTATE_ANIMA,       //���Ŷ���
    SKILLSTATE_ONAIR        //��������ʹ��
};

//��Ҽ���ID
enum PlayerSkillID
{
    ID_FREEZE = 0X10001,    //����
    ID_CONFUSE,             //�Ȼ�          
};



#endif//__SKILL_H__