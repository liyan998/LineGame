#include "GameElement.h"

bool CCat::init()
{
    CNpc::init();

    m_iCategory = Category::CATEGORY_CAT;

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_CAT,
        RES_ANIMA_PLS_CAT,
        RES_ANIMA_JSO_CAT
        );


    return true;
}

void CCat::onEnter()
{
    CNpc::onEnter();



}



void CCat::run(float time)
{
    CNpc::run(time);
    CNpc::changeLiveDie(time);


}

void CCat::animation_move()
{
    CAnimationAxis* aa = findCreateByIndex(INDEX_CAT);

    aa->setCurrentAnimation(ARMATURE_CAT);
    aa->getArmature()->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CNpc::movementCallback));

    aa->getArmature()->getAnimation()->play(PLAYLAB_CAT_WALK_FRONT);
//     setCurrentAnimation(ARMATURE_CAT);
//     getArmature()->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CNpc::movementCallback));
//     getArmature()->getAnimation()->play(PLAYLAB_DYB_FRONT_WALK);

}


