#ifndef __ACTOR_H__
#define __ACTOR_H__

//#include "GameElement.h"

class CActor : public CGameElement
{                            


public:
    CGamePlayer*        m_refPlayer;
    CMySprite*          m_refSp;

protected:

    
    int                 m_iDirect;      //����     
};


#endif//__ACTOR_H__