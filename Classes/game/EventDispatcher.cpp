#include "EventSystem.h"

#include <thread>
//#include "System.h"


CEventDispatcher* m_pEvent = nullptr;

CEventDispatcher::~CEventDispatcher()
{
   
}


CEventDispatcher* CEventDispatcher::getInstrance()
{
    if (m_pEvent == nullptr)
    {                                     
        m_pEvent = new CEventDispatcher();
    }

    return m_pEvent;
}


void CEventDispatcher::regsiterEvent(int eventid, CEventHandler* pHandler)
{     
    Iter_AllEVentHandler iter_eventhandler = m_oAllHandler.find(eventid);
 
    T_AllEventHandler* tvector;

    if (iter_eventhandler != m_oAllHandler.end())
    {                                      
        tvector = iter_eventhandler->second;

        for (Iter_AllHandler iter = tvector->begin(); iter != tvector->end();++iter)
        {                      
            if (*iter == pHandler)
            {                  
                return;
            }
        }                        
        tvector->push_back(pHandler);       
    }
    else
    {                                        
        tvector = new T_AllEventHandler();
        tvector->push_back(pHandler);        
        m_oAllHandler.insert(Pair_EventHandler(eventid, tvector));
    } 
}


void CEventDispatcher::unRegsiterEvent(int eventid, CEventHandler* pHandler)
{

    Iter_AllEVentHandler iter_eventhandler = m_oAllHandler.find(eventid);

    if (iter_eventhandler != m_oAllHandler.end())
    {
        T_AllEventHandler* pAllHandler = iter_eventhandler->second;
        for (Iter_AllHandler iter = pAllHandler->begin(); iter != pAllHandler->end(); ++iter)
        {                                  
            if (pHandler == (*iter))
            {
                //log("===");
                pAllHandler->erase(iter);
                break;
            }  
        }

        //log("__Size%d", pAllHandler->size());
    }
}



void CEventDispatcher::dispatchEvent(int eventid, EventParm parm)
{        

    
    Iter_AllEVentHandler iter_eventhandler = m_oAllHandler.find(eventid);

    if (iter_eventhandler != m_oAllHandler.end())
    {
        T_AllEventHandler* pAllHandler = iter_eventhandler->second;  

        if (pAllHandler->size() < 1)
        {
            return;
        }
        
        for (Iter_AllHandler iter = pAllHandler->begin(); iter != pAllHandler->end(); ++iter)
        {
            (*iter)->actionEvent(eventid, parm);
        } 
         
    }


    if (parm != PARM_NULL)
    {
        delete parm;
        //parm = nullptr;
    }

    
}


void CEventDispatcher::released()
{
    for (Iter_AllEVentHandler iter = m_oAllHandler.begin(); iter != m_oAllHandler.end();++iter)
    {  
        T_AllEventHandler* pAlleventhandler = iter->second;
        pAlleventhandler->clear();

        delete iter->second;
    }

    m_oAllHandler.clear();
   
    delete m_pEvent;
    m_pEvent = nullptr;
}








