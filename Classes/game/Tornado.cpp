#include "GameElement.h"


bool CTornado::init()
{
    CEnemy::init();

    m_iCategory = Category::CATEGORY_TORNADO;
    
    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_DRAGON_SKILL_TORNADO,
        RES_ANIMA_PLS_DRAGON_SKILL_TORNADO,
        RES_ANIMA_JSO_DRAGON_SKILL_TORNADO
        );
    
    return true;
}


void CTornado::onEnter()
{    CEnemy::onEnter();

    setCurrentAnimation(ARMATURE_DRAGON_SKILL_TORNADO);
  
}


void CTornado::released()
{
    clearCurrentAnimation();
}


void CTornado::run(float time)
{
    if (m_State == State::STATE_LIVE)
    {
        CEnemy::checkWithMove();
    }
}


void CTornado::changeDirect(int direct)
{

}

void CTornado::setState(int state)
{
    this->m_State = state;

    switch (state)
    {
    case STATE_LIVE:
        this->setVisible(true);
        break;
    case STATE_DISAPPEAR:
        this->setVisible(false);
        break;
    }
}

void CTornado::setStyle(int color)
{
    switch (color)
    {
    case T_SkillDrogTornado::TORNADO_COLOR_WHITE:
        getArmature()->getAnimation()->play(PLAYLAB_DRAGON_SKILL_TORNADO_WHITE);
        break;
    case T_SkillDrogTornado::TORNADO_COLOR_BLACK:
        getArmature()->getAnimation()->play(PLAYLAB_DRAGON_SKILL_TORNADO_BLACK);
        break;
    }
}