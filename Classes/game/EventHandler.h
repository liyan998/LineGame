#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__



class CEventHandler
{

public:

    virtual void actionEvent(int eventid, EventParm pData) = 0;

};

#endif//__EVENTHANDLER_H__