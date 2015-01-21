#ifndef __EVENTSYSTEM_H__
#define __EVENTSYSTEM_H__

#include <map>
#include <vector>  



#define PARM_NULL                           0

//////////////////////////////////////////////////////////////////////////////

#define EVENT_CLOSE                         0x10000001      //闭合
#define EVENT_WIN                           0x10000002      //胜利
#define EVENT_TIMEOUT                       0x10000003      //超时
#define EVENT_PLAYERDIE                     0x10000004      //玩家死亡
#define EVENT_HIT                           0x10000005      //收到攻击

#define EVENT_PROPERTY_ADDHEALTH            0x10000006      //道具 增加生命值
#define EVENT_PROPERTY_ADDTIME              0x10000007      //道具 增加时间
#define EVENT_PROPERTY_ADDPROTECT           0x10000008      //道具 增加防护
#define EVENT_PROPERTY_ADDSPEED             0x10000009      //道具 增加速度

#define EVENT_BOSSSKILL_START               0x10000100      //BOSS技能释放开始
#define EVENT_BOSSSKILL_END                 0x10000101      //BOSS技能释放结束

#define EVENT_BOSSSKILL_LIIGHTATTICAK       0x10000102      //BOSS技能 伤害
#define EVENT_BOSSSKILL_LIGHTATTICAKOVER    0x10000103      //闪电攻击完成
#define EVENT_BOSSSKILL_LIGHTCOUNT          0X10000104      //闪电计数

#define EVENT_BOSSSKILL_TORNADO_SURROUND    0x10000105      //风魔龙技能龙卷风圈住
#define EVENT_BOSSSKILL_TORNADO_CHANAGE     0x10000106      //龙卷风技能改变颜色

#define EVENT_PLAYERSKILL_CONFUSE           0x10000201      //玩家魅惑技能



///////////////////////////////////////////////////////////////////////////////////


//道具增加速度
struct T_EventPropertyAddSpeed
{
    int time;           //持续时间

    float addPart;      //增加百分比

    static T_EventPropertyAddSpeed* clone(T_EventPropertyAddSpeed* pEffAdd)
    {
        struct T_EventPropertyAddSpeed* pNEffAdd = new struct T_EventPropertyAddSpeed;
        pNEffAdd->time          = pEffAdd->time;
        pNEffAdd->addPart       = pEffAdd->addPart;

        return pNEffAdd;
    }
};


/////////////////////////////////////////////////////////////////////////////////////////

class CEventHandler;            

typedef std::vector< CEventHandler* >                       T_AllEventHandler;
typedef T_AllEventHandler::iterator                         Iter_AllHandler;
typedef std::map<int, T_AllEventHandler*>::iterator         Iter_AllEVentHandler;
typedef std::pair<int,  T_AllEventHandler* >                Pair_EventHandler;
typedef void*                                               EventParm;        

#include "EventDispatcher.h"
#include "EventHandler.h"     


#endif//__EVENTSYSTEM_H__