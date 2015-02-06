#include "GameElement.h"

bool CCat::init()
{
    CNpc::init();

    m_iCategory     = Category::CATEGORY_CAT;
    


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

void CCat::animation_stop()
{
    CAnimationAxis* aa = findCreateByIndex(INDEX_CAT);
    aa->getArmature()->getAnimation()->pause();
}



void CCat::collwithPlayerCallBack()
{
    if (m_refPlayer->getSealState() == CGamePlayer::SealState::SEALSTATE_NONE)
    {
        CEventDispatcher::getInstrance()->dispatchEvent(EVENT_CAT_SEAL, new int(CGamePlayer::SealState::SEALSTATE_ONAIR));
    }    
}