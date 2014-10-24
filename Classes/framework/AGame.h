/************************************************************************/
/* 

作者:     严黎刚
日期:     2014-10-20

*/
/************************************************************************/
#ifndef __AGAME_H__
#define __AGAME_H__


#include "framework/ui/UIFrameWork.h"

namespace liyan998
{
    class CAGame
    {
    public:

        enum State
        {
            STATE_INIT,                                                         //
            STATE_RUN,                                                          //
            STATE_STOP,                                                         //
            STATE_DESTROY                                                       //
        };

    public:

        virtual void setState(State) = 0;                                       //

        inline State getState()
        {
            return m_State;
        };                                                                      //

    protected:

        State                                           m_State;                //
        

    };    
}

#endif//__AGAME_H__