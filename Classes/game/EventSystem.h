#ifndef __EVENTSYSTEM_H__
#define __EVENTSYSTEM_H__

#include <map>
#include <vector>  



#define PARM_NULL                           0

//////////////////////////////////////////////////////////////////////////////

#define EVENT_CLOSE                         0x10000001      //�պ�
#define EVENT_WIN                           0x10000002      //ʤ��
#define EVENT_TIMEOUT                       0x10000003      //��ʱ
#define EVENT_PLAYERDIE                     0x10000004      //�������
#define EVENT_HIT                           0x10000005      //�յ�����

#define EVENT_PROPERTY_ADDHEALTH            0x10000006      //���� ��������ֵ
#define EVENT_PROPERTY_ADDTIME              0x10000007      //���� ����ʱ��
#define EVENT_PROPERTY_ADDPROTECT           0x10000008      //���� ���ӷ���
#define EVENT_PROPERTY_ADDSPEED             0x10000009      //���� �����ٶ�

#define EVENT_BOSSSKILL_START               0x10000100      //BOSS�����ͷſ�ʼ
#define EVENT_BOSSSKILL_END                 0x10000101      //BOSS�����ͷŽ���

#define EVENT_BOSSSKILL_LIIGHTATTICAK       0x10000102      //BOSS���� �˺�
#define EVENT_BOSSSKILL_LIGHTATTICAKOVER    0x10000103      //���繥�����
#define EVENT_BOSSSKILL_LIGHTCOUNT          0X10000104      //�������

#define EVENT_BOSSSKILL_TORNADO_SURROUND    0x10000105      //��ħ�����������Ȧס
#define EVENT_BOSSSKILL_TORNADO_CHANAGE     0x10000106      //����缼�ܸı���ɫ

#define EVENT_PLAYERSKILL_CONFUSE           0x10000201      //����Ȼ���



///////////////////////////////////////////////////////////////////////////////////


//���������ٶ�
struct T_EventPropertyAddSpeed
{
    int time;           //����ʱ��

    float addPart;      //���Ӱٷֱ�

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