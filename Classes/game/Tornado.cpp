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
{
    CEnemy::onEnter();

    setCurrentAnimation(ARMATURE_DRAGON_SKILL_TORNADO);
    getArmature()->getAnimation()->play(PLAYLAB_DRAGON_SKILL_TORNADO_BLACK);
}


void CTornado::released()
{

}


void CTornado::run(float time)
{
    CEnemy::checkWithMove();
}


void CTornado::changeDirect(int direct)
{

}

void CTornado::setState(int state)
{

}