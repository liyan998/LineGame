#ifndef __ANIMAAXIS_H__
#define __ANIMAAXIS_H__


#include "System.h"

#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h" 

#include "GameResMacros.h"

using namespace cocostudio;

class CAnimationAxis :public Layer
{

public:

    CAnimationAxis() :m_pArmature(nullptr)
    {
     
    
    }

    CREATE_FUNC(CAnimationAxis)


    

    void clearCurrentAnimation();

    void setCurrentAnimation(const char* arname);


    Armature*           m_pArmature;
};

#endif//__ANIMAAXIS_H__