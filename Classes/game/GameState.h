#ifndef __STATE_H__
#define __STATE_H__         

class CGameState
{

public:

    virtual void setState(int state) = 0;       // 

    virtual void released() = 0;

    inline int getState()
    {
        return m_State;
    };


protected:

    int m_State;
};
#endif