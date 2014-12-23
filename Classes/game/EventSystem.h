#ifndef __EVENTSYSTEM_H__
#define __EVENTSYSTEM_H__

#include <map>
#include <vector>   


#define EVENT_TEST      0x00000001

#define EVENT_CLOSE     0x10000001      //±ÕºÏ
#define EVENT_WIN       0x10000002      //
#define EVENT_TIMEOUT   0x10000003      //³¬Ê±



class CEventHandler;             

typedef std::vector< CEventHandler* >                       T_AllEventHandler;
typedef T_AllEventHandler::iterator                         Iter_AllHandler;  
typedef std::map<int, T_AllEventHandler*>::iterator         Iter_AllEVentHandler;
typedef std::pair<int,  T_AllEventHandler* >                Pair_EventHandler;   
typedef void*                                               EventParm;        

#include "EventDispatcher.h"
#include "EventHandler.h"     


#endif//__EVENTSYSTEM_H__