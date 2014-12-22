#ifndef __ACTOR_H__
#define __ACTOR_H__

//#include "GameElement.h"

class CActor : public CGameElement
{                            
public:

    CMySprite*          m_refSp;

protected:

    
    int                 m_iDirect;      //·½Ïò     
};


#endif//__ACTOR_H__