#include "AnimaAxis.h"

void CAnimationAxis::setCurrentAnimation(const char* arname)
{
    if (
        m_pArmature != nullptr &&
        strcmp(arname, m_pArmature->getAnimation()->getCurrentMovementID().c_str()) == 0
        )
    {
        return;
    }

    clearCurrentAnimation();

    m_pArmature = Armature::create(arname);
    //m_pSp->getAnimation()->setMovementEventCallFunc(this, callback);
    addChild(m_pArmature);
}


void CAnimationAxis::clearCurrentAnimation()
{
    if (m_pArmature != nullptr)
    {
        m_pArmature->getAnimation()->setMovementEventCallFunc(this, nullptr);
        m_pArmature->getAnimation()->setFrameEventCallFunc(nullptr);
        removeChild(m_pArmature);
        m_pArmature = nullptr;
    }
}
