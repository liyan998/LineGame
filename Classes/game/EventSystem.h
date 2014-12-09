#ifndef __EVENTSYSTEM_H__
#define __EVENTSYSTEM_H__

#include <map>
#include <vector>   


#define EVENT_TEST   0x1000001 


class CEventHandler;             

typedef std::vector< CEventHandler* >                       T_AllEventHandler;
typedef T_AllEventHandler::iterator                         Iter_AllHandler;  
typedef std::map<int, T_AllEventHandler*>::iterator         Iter_AllEVentHandler;
typedef std::pair<int,  T_AllEventHandler* >                Pair_EventHandler;   
typedef void*                                               EventParm;        

#include "EventDispatcher.h"
#include "EventHandler.h"     


#endif//__EVENTSYSTEM_H__