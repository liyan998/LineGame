#ifndef __ANIMAAXIS_H__
#define __ANIMAAXIS_H__


#include "System.h"

#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h" 


using namespace cocostudio;

class CAnimationAxis :public Layer
{

public:

    CAnimationAxis() :m_pSp(nullptr){}

    void clearCurrentAnimation();

    void setCurrentAnimation(const char* arname);


    Armature*           m_pSp;
};

#endif//__ANIMAAXIS_H__