#ifndef __SKILL_H__
#define __SKILL_H__

enum SkillConfuseState
{
    SKILLSTATE_CD,      //技能CD
    SKILLSTATE_READY,   //可释放

    SKILLSTATE_NONE,    //技能未被使用
    SKILLSTATE_ANIMA,   //播放动画
    SKILLSTATE_ONAIR    //技能正在使用
};

#endif//__SKILL_H__