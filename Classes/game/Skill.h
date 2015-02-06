#ifndef __SKILL_H__
#define __SKILL_H__
/************************************************************************/
/* 
@berf 玩家技能
@auth 
*/
/************************************************************************/

//魅惑技能状态
enum SkillConfuseState
{
    SKILLSTATE_CD,          //技能CD
    SKILLSTATE_READY,       //可释放

    SKILLSTATE_NONE,        //技能未被使用
    SKILLSTATE_ANIMA,       //播放动画
    SKILLSTATE_ONAIR        //技能正在使用
};

//玩家技能ID
enum PlayerSkillID
{
    ID_FREEZE = 0X10001,    //冰冻
    ID_CONFUSE,             //魅惑          
};



#endif//__SKILL_H__