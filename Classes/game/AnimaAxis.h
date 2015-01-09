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

    enum ElementIndex
    {
        IndexArmature = 0xffffff
    };

    CAnimationAxis() :m_pArmature(nullptr){}

    CREATE_FUNC(CAnimationAxis)


    Armature* getArmature();

    void clearCurrentAnimation();

    void setCurrentAnimation(const char* arname);


    Armature*           m_pArmature;
};

#endif//__ANIMAAXIS_H__