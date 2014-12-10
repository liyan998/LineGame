/************************************************************************/
/* 




*/
/************************************************************************/
#ifndef __EVENTDISPATCHER_H__
#define __EVENTDISPATCHER_H__



#include "EventSystem.h"


struct T_Event
{
    int evenid;

    EventParm ep;
};


class CEventDispatcher
{
public:

    
    ~CEventDispatcher();

    static CEventDispatcher* getInstrance();

    void regsiterEvent( int eventid , CEventHandler* pHandler);

    void unRegsiterEvent(int eventid, CEventHandler* pHandler);

    void dispatchEvent(int eventid, EventParm param); 

    void released();

private:


private:

    static CEventDispatcher* m_pEventDis;

private:

    std::map<int, T_AllEventHandler* >  m_oAllHandler;

    std::vector<T_Event*>               m_oMessageQue;

};


#endif//__EVENTDISPATCHER_H__