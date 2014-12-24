#ifndef __EVENTSYSTEM_H__
#define __EVENTSYSTEM_H__

#include <map>
#include <vector>  

#define PARM_NULL                       0

#define EVENT_CLOSE                     0x10000001      //闭合

#define EVENT_WIN                       0x10000002      //

#define EVENT_TIMEOUT                   0x10000003      //超时

#define EVENT_PLAYERDIE                 0x10000004      //玩家死亡

#define EVENT_HIT                       0x10000005      //收到攻击

#define EVENT_PRORETY_ADDHEALTH         0x10000006      //道具 增加生命值




class CEventHandler;             

typedef std::vector< CEventHandler* >                       T_AllEventHandler;

typedef T_AllEventHandler::iterator                         Iter_AllHandler; 

typedef std::map<int, T_AllEventHandler*>::iterator         Iter_AllEVentHandler;

typedef std::pair<int,  T_AllEventHandler* >                Pair_EventHandler;   

typedef void*                                               EventParm;        

#include "EventDispatcher.h"
#include "EventHandler.h"     


#endif//__EVENTSYSTEM_H__