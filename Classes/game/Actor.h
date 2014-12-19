#ifndef __ACTOR_H__
#define __ACTOR_H__

//#include "GameElement.h"

class CActor : public CGameElement, public CGameState
{                            


protected:

    int             m_iStep;        //移动速度
    int             m_iDirect;      //方向     
};


#endif//__ACTOR_H__