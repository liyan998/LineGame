#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "GameElement.h"

class CActor : public CGameElement
{   
public:

    virtual void run(float time) = 0;

protected:

    int             m_iStep;

};


#endif//__ACTOR_H__