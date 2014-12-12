#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "GameElement.h"

class CActor : public CGameElement
{                            
protected:

    int             m_iStep; //ÒÆ¶¯ËÙ¶È
    int             m_iDirect;
};


#endif//__ACTOR_H__