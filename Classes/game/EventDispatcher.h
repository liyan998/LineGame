/************************************************************************/
/* 




*/
/************************************************************************/
#ifndef __EVENTDISPATCHER_H__
#define __EVENTDISPATCHER_H__



#include "EventSystem.h"


class CEventDispatcher
{
public:

    static CEventDispatcher* getInstrance();

    void regsiterEvent( int eventid , CEventHandler* pHandler);

    void unRegsiterEvent(int eventid, CEventHandler* pHandler);

    void dispatchEvent(int eventid, EventParm param);

private:

    static CEventDispatcher* m_pEventDis;

private:

    std::map<int, T_AllEventHandler* > m_oAllHandler;


};


#endif//__EVENTDISPATCHER_H__