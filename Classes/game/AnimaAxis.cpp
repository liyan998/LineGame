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

Armature* CAnimationAxis::getArmature()
{
    return m_pArmature;
}

void CAnimationAxis::clearCurrentAnimation()
{
   

    if (m_pArmature != nullptr)
    {
      
        m_pArmature->getAnimation()->setMovementEventCallFunc(this, nullptr);
        m_pArmature->getAnimation()->setFrameEventCallFunc(nullptr);
       
        m_pArmature->getAnimation()->stop();  //这句有没有都会崩
        m_pArmature->runAction(
            Sequence::create(DelayTime::create(.1f), 
            CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, m_pArmature)),
            NULL)
            );
        //removeChild(m_pArmature);
        m_pArmature->removeFromParentAndCleanup(true);
        m_pArmature = nullptr;
    }
}

