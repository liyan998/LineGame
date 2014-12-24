#include "AnimaAxis.h"

void CAnimationAxis::setCurrentAnimation(const char* arname)
{
    if (
        m_pSp != nullptr &&
        strcmp(arname, m_pSp->getAnimation()->getCurrentMovementID().c_str()) == 0
        )
    {
        return;
    }

    clearCurrentAnimation();

    m_pSp = Armature::create(arname);
    //m_pSp->getAnimation()->setMovementEventCallFunc(this, callback);
    addChild(m_pSp);
}


void CAnimationAxis::clearCurrentAnimation()
{
    if (m_pSp != nullptr)
    {
        m_pSp->getAnimation()->setMovementEventCallFunc(this, nullptr);
        m_pSp->getAnimation()->setFrameEventCallFunc(nullptr);
        removeChild(m_pSp);
        m_pSp = nullptr;
    }
}
